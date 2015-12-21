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

namespace {

CMatrix load_png(const char* fName) {
    png_structp png_read_ptr;
    png_infop info_read_ptr;
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    int compression_type, filter_method;
    int row, col;
    png_bytep *row_pointers;
    char sigBuf[PNG_BYTES_TO_CHECK];

    FILE *fpIn;

    fpIn = stdin;
    assert(fpIn = fopen(fName , "r"));

    assert(fread(sigBuf, 1, PNG_BYTES_TO_CHECK, fpIn) == PNG_BYTES_TO_CHECK);

    assert(png_sig_cmp((png_byte*)sigBuf, (png_size_t)0, PNG_BYTES_TO_CHECK) == false);

    png_read_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_read_ptr != NULL);

    info_read_ptr = png_create_info_struct(png_read_ptr);
    assert(info_read_ptr != NULL);

    assert(setjmp(png_jmpbuf(png_read_ptr)) == false);

    png_init_io(png_read_ptr, fpIn);

    png_set_sig_bytes(png_read_ptr, PNG_BYTES_TO_CHECK);

    png_read_png(png_read_ptr, info_read_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

    fclose(fpIn);

    png_get_IHDR(png_read_ptr, info_read_ptr, &width, &height, &bit_depth,
    &color_type, &interlace_type, &compression_type, &filter_method);

    row_pointers = png_get_rows (png_read_ptr, info_read_ptr);

    CMatrix IMAGE(width, height);
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            IMAGE[row][col] = row_pointers[row][col];
        };
    };
    return IMAGE;
}

}
#endif


TrainingSet::TrainingSet()
{
}

#ifdef ENABLE_PNG
TrainingSet::TrainingSet(const char* fName, int inRowFrames, int inColFrames)
{
    std::fstream test(fName);
    assert(test.is_open());
    test.close();
    const CMatrix img(load_png(fName));
    CSize frameSize(img.width() / inRowFrames,
                    img.height() / inColFrames);
    this->resize(inRowFrames * inColFrames);
    for (int i(0); i != inRowFrames; ++i) {
        for (int j(0); j != inColFrames; ++j) {
	    TrainingSample& cur((*this)[i * inColFrames + j]);
	    cur.resize(frameSize.width() * frameSize.height());
            for (int k(0); k != frameSize.width(); ++k) {
                for (int l(0); l != frameSize.height(); ++l) {
                    (*this)[i * inColFrames + j][k * frameSize.height() + l]
                            = img[i * frameSize.width() + k][j * frameSize.height() + l];
                }
            }
        }
    }
}
#endif

#ifdef QT_AVAILABLE
TrainingSet::TrainingSet(const QList<QImage>& l)
{
    this->reserve(l.size());
    for (const QImage& i : l) {
        this->push_back(i);
    }
}
#endif
