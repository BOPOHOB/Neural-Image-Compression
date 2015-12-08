#ifndef TRAININGSET_H
#define TRAININGSET_H

#include <vector>
#include "trainingsample.h"

class TrainingSet : std::vector<TrainingSample>
{
public:
    TrainingSet();
};

#endif // TRAININGSET_H
