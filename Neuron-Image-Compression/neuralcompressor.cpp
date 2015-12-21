#include "neuralcompressor.h"

#include <cassert>
#include <png.h>

#ifdef QT_AVAILABLE
#include <QPixmap>
#endif

#include "trainingset.h"
#include <cmath>
#include "trainingset.h"
#include <fstream>
#include <cassert>
#include "kernel/csize.h"
#include "kernel/cmatrix.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#ifdef QT_AVAILABLE
#include <QImage>
#endif

#ifdef ENABLE_PNG
#define PNG_BYTES_TO_CHECK 4

#include <png.h>
#endif

namespace {

template <typename T>
T sqr(const T& v) { return v * v; }

struct DistanceItemCompare {
    bool operator()(const NeuralSpan::DistanceItem& a, const NeuralSpan::DistanceItem& b) const { return a.second < b.second; }
};

#ifdef ENABLE_PNG
void save_png(const char* fName, const char* exampleFName, const CMatrix& IMAGE) {
    png_structp png_read_ptr;
    png_infop info_read_ptr;
    png_structp png_write_ptr;
    png_infop info_write_ptr;
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    int compression_type, filter_method;
    int row, col;
    png_bytep *row_pointers;
    char sigBuf[PNG_BYTES_TO_CHECK];

    FILE *fpIn;
    FILE *fpOut;

    fpIn = stdin;
    assert(fpIn = fopen(exampleFName, "r"));

    assert(fread(sigBuf, 1, PNG_BYTES_TO_CHECK, fpIn) == PNG_BYTES_TO_CHECK);

    assert(png_sig_cmp((png_byte*)sigBuf, (png_size_t)0, PNG_BYTES_TO_CHECK) == false);

    png_read_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_read_ptr);

    info_read_ptr = png_create_info_struct(png_read_ptr);
    assert(info_read_ptr);

    assert(setjmp(png_jmpbuf(png_read_ptr)) == false);

    png_init_io(png_read_ptr, fpIn);

    png_set_sig_bytes(png_read_ptr, PNG_BYTES_TO_CHECK);

    png_read_png(png_read_ptr, info_read_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

    fclose(fpIn);

    png_get_IHDR(png_read_ptr, info_read_ptr, &width, &height, &bit_depth,
    &color_type, &interlace_type, &compression_type, &filter_method);

    assert(color_type == 0);
    assert(bit_depth == 8);

    row_pointers = png_get_rows (png_read_ptr, info_read_ptr);

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            row_pointers[row][col] = IMAGE[row][col];
        }
    }

    fpOut = stdout;
    assert(fpOut = fopen(fName, "w"));

    png_write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_write_ptr != NULL);

    info_write_ptr = png_create_info_struct(png_write_ptr);
    assert(info_write_ptr != NULL);

    assert(setjmp(png_jmpbuf(png_write_ptr)) == false);

    png_set_IHDR(png_write_ptr, info_write_ptr, width, height, bit_depth,
    color_type, interlace_type, compression_type, filter_method);
    png_set_rows (png_write_ptr, info_write_ptr, row_pointers);

    png_init_io(png_write_ptr, fpOut);
    png_write_png(png_write_ptr, info_write_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);


    png_destroy_read_struct(&png_read_ptr, &info_read_ptr, png_infopp_NULL);
    fclose(fpOut);
}
#endif


}

CMatrix::T NeuralCompressor::ETA = 0.5;


NeuralCompressor::NeuralCompressor(const TrainingSet& s, int l, const CSize frameSize,  const CSize imageSize)
    : weights(s.front().size(), l)
    , image(imageSize)
    , frame(frameSize)
{
    assert(frameSize.width() * frameSize.height() == static_cast<int>(s.front().size()));

    const double SIGMA(1);
    CArray modes;
    modes.fill(1.0, l);

    for (int CKOKA_PA3(10); CKOKA_PA3--;) {
        for (TrainingSet::const_iterator it(s.begin());  it != s.end(); ++it) {
            const TrainingSample& sample(*it);
            NeuralSpan::Distances g(weights.distance(sample));
            for (int i(0); i != g.size(); ++i) {
        	g[i].second *= modes[i];
            }
            std::sort(g.begin(), g.end(), DistanceItemCompare());

            for (int i(0); i != g.size(); ++i) {
                CMatrix::T* datum(weights[g[i].first]);
                const CMatrix::T dK(exp(-static_cast<double>(i) / SIGMA));
                modes[g[i].first] += dK;
                for (int j(0); j != sample.size(); ++j) {
                    datum[j] += ETA * dK * (sample[j] - datum[j]);
                }
            }
        }
        weights.clearPotential();
    }
    
    CArray v;
    v.fill(0.0, l);

    for (TrainingSet::const_iterator it(s.begin());  it != s.end(); ++it) {
	const int nearest(weights.nearest(*it));
        conformity.insert(ConformityItem(nearest, it - s.begin()));
        v[nearest]++;
    }
#ifdef SHOW_HISTOGRAM
    for (int i(0); i != l; ++i) {
        std::cout << i << ": " << v[i] << std::endl;
    }
#endif
}

#ifdef ENABLE_PNG
void NeuralCompressor::saveAs(const char* fname, const char* exampleFName) const
{
    CMatrix img(image.width() * 2, image.height() * 2);
    const int height(image.height() / frame.height() + 1);
    for (Conformity::const_iterator it(conformity.begin()); it != conformity.end(); ++it) {
        const CMatrix::T* datum(weights[it->first]);
        const int j0((it->second % height) * frame.height());
        const int k0((it->second / height) * frame.width());
        for (int j(0); j != frame.height(); ++j) {
            for (int k(0); k != frame.width(); ++k) {
                const double& v(datum[j * frame.width() + k]);
                img[k0 + k][j0 + j] = v;
            }
        }
    }
    save_png(fname, exampleFName, img);
}
#endif

#ifdef QT_AVAILABLE
QPixmap NeuralCompressor::recoverQPixmap() const
{
    QImage img(image.width(), image.height(), QImage::Format_RGB32);
    const int height(image.height() / frame.height());
    for (Conformity::const_iterator it(conformity.begin()); it != conformity.end(); ++it) {
        const CMatrix::T* datum(weights[it->first]);
        const int j0((it->second % height) * frame.height());
        const int k0((it->second / height) * frame.width());
        for (int j(0); j != frame.height(); ++j) {
            for (int k(0); k != frame.width(); ++k) {
                const double& v(datum[j * frame.width() + k]);
                img.setPixel(k0 + k, j0 + j, qRgb(v, v, v));
            }
        }
    }
    return QPixmap::fromImage(img);
}
#endif
