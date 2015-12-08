#include "neuralcompressor.h"

#include "trainingset.h"
#ifdef QT_AVAILABLE
#include <QPixmap>
#endif

NeuralCompressor::NeuralCompressor()
{

}

NeuralCompressor::NeuralCompressor(const TrainingSet&)
{

}

#ifdef QT_AVAILABLE
QPixmap NeuralCompressor::recoverToQPixmap()
{
    return QPixmap();
}
#endif

