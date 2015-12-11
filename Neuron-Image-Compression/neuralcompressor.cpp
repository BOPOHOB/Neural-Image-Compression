#include "neuralcompressor.h"

#include <cassert>

#ifdef QT_AVAILABLE
#include <QPixmap>
#endif

#include "trainingset.h"

namespace {

double sqr(const double& v) { return v * v; }

}


NeuralCompressor::NeuralCompressor(const TrainingSet& s, const int l,  const int rowFramesCount, const CSize frameSize)
    : in(s.front().size(), l)
    , out(l, s.front().size())
    , width(rowFramesCount)
    , frame(frameSize)
{
    assert(frameSize.width() * frameSize.height() == static_cast<int>(s.front().size()));

    //teaching...
    qDebug() << "teaching. . . " << e(s);

    data.resize(s.size());
    TrainingSet::const_iterator sIt(s.begin());
    for (CompressedData::iterator it(data.begin()); it != data.end(); ++it, ++sIt) {
        *it = in * *sIt;
    }
}

#ifdef QT_AVAILABLE
QPixmap NeuralCompressor::recoverQPixmap() const
{
    QImage img(frame.width() * width, frame.height() * data.size() / width, QImage::Format_RGB32);
    for (int i(0); i != static_cast<int>(data.size()); ++i) {
        const CVector datum(out * data[i]);
        const int j0((i % width) * frame.width());
        const int k0((i / width) * frame.height());
        for (int j(0); j != frame.width(); ++j) {
            for (int k(0); k != frame.height(); ++k) {
                const double& v(datum[j * frame.height() + k]);
                img.setPixel(j0 + j, k0 + k, qRgb(v, v, v));
            }
        }
    }
    return QPixmap::fromImage(img);
}
#endif

double NeuralCompressor::e(const TrainingSet& wholeX)
{
    double sum(0.0);
    const CMatrix p(out * in);
    for (TrainingSet::const_iterator it(wholeX.begin()); it != wholeX.end(); ++it) {
        const TrainingSample& x(*it);
        const CVector h(p * x);
        CVector::const_iterator hIt(h.begin()), xIt(x.begin());
        const CVector::const_iterator end(h.end());
        for (; hIt != end; ++hIt, ++xIt) {
            sum += sqr(*hIt - *xIt);
        }
    }
    return 0.5 * sum;
}
