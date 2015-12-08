#ifndef TRAININGSET_H
#define TRAININGSET_H

#include <vector>
#include "trainingsample.h"
#ifdef QT_AVAILABLE
#include <QList>
class QImage;
#endif

class TrainingSet : std::vector<TrainingSample>
{
public:
    TrainingSet();

#ifdef QT_AVAILABLE
    TrainingSet(const QList<QImage>&);
#endif
};

#endif // TRAININGSET_H
