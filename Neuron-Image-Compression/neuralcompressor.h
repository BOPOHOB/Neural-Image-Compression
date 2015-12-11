#ifndef NEURALCOMPRESSOR_H
#define NEURALCOMPRESSOR_H
#ifdef QT_AVAILABLE
class QPixmap;
#endif
class TrainingSet;
#include "kernel/csize.h"
#include "neuralspan.h"

class NeuralCompressor
{
    double e(const TrainingSet &wholeX);
public:
    NeuralCompressor(const TrainingSet&, const int l, const int rowFramesCount, const CSize frameSize);

#ifdef QT_AVAILABLE
    QPixmap recoverQPixmap() const;
#endif
private:
    NeuralSpan in;
    NeuralSpan out;

    typedef std::vector<CVector> CompressedData;
    CompressedData data;
    int width;
    CSize frame;
};

#endif // NEURALCOMPRESSOR_H
