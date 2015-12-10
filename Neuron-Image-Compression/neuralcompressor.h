#ifndef NEURALCOMPRESSOR_H
#define NEURALCOMPRESSOR_H
#ifdef QT_AVAILABLE
class QPixmap;
#endif
class TrainingSet;
#include "neuralspan.h";

class NeuralCompressor
{
    double e(const TrainingSet &wholeX);
public:
    NeuralCompressor(const TrainingSet&, const int l);

#ifdef QT_AVAILABLE
    QPixmap recoverQPixmap();
#endif
private:
    NeuralSpan in;
    NeuralSpan out;
};

#endif // NEURALCOMPRESSOR_H
