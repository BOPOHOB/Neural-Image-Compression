#ifndef NEURALCOMPRESSOR_H
#define NEURALCOMPRESSOR_H
#ifdef QT_AVAILABLE
class QPixmap;
#endif
class TrainingSet;

class NeuralCompressor
{
public:
    NeuralCompressor();
    NeuralCompressor(const TrainingSet&);

#ifdef QT_AVAILABLE
    QPixmap recoverToQPixmap();
#endif
};

#endif // NEURALCOMPRESSOR_H
