#include "neuralcompressor.h"

#include "trainingset.h"
#ifdef QT_AVAILABLE
#include <QPixmap>
#endif

namespace {

double sqr(const double& v) { return v * v; }

}


NeuralCompressor::NeuralCompressor(const TrainingSet& s, const int l)
    : in(l, s.front().size())
    , out(s.front().size(), l)
{
    qDebug() << in << out;
}

#ifdef QT_AVAILABLE
QPixmap NeuralCompressor::recoverQPixmap()
{
    return QPixmap();
}
#endif

double NeuralCompressor::e(const TrainingSet& wholeX)
{
    double sum(0.0);
    const CMatrix p(in * out);
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
