#include "neuralcompressor.h"

#include <cassert>

#ifdef QT_AVAILABLE
#include <QPixmap>
#endif

#include "trainingset.h"

namespace {

double sqr(const double& v) { return v * v; }

}

CMatrix::T NeuralCompressor::ETA = 0.3;


NeuralCompressor::NeuralCompressor(const TrainingSet& s, const int l, const CSize frameSize,  const CSize imageSize)
    : weights(s.front().size(), l)
    , image(imageSize)
    , frame(frameSize)
{
    assert(frameSize.width() * frameSize.height() == static_cast<int>(s.front().size()));

    for (int o(10); --o;) {
        for (TrainingSet::const_iterator it(s.begin());  it != s.end(); ++it) {
            const int i(weights.nearest(*it));
            conformity.insert(ConformityItem(i, it - s.begin()));
            CMatrix::T* datum(weights[i]);
            const TrainingSample& sample(*it);
            for (int j(0); j != sample.size(); ++j) {
                datum[j] += ETA * (sample[j] - datum[j]) * (datum[j] / 255.0);
            }
            if ((it - s.begin()) % 100 == 0) {
                qDebug() << it - s.begin() << i;
            }
        }
        weights.clearPotential();
    }
}

#ifdef QT_AVAILABLE
QPixmap NeuralCompressor::recoverQPixmap() const
{
    QImage img(image.width(), image.height(), QImage::Format_RGB32);
    const int height(image.height() / frame.height());
    qDebug() << image.width() << image.height();
    qDebug() << frame.width() << frame.height();

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
