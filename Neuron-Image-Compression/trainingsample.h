#ifndef TRAININGSAMPLE_H
#define TRAININGSAMPLE_H

#include <vector>
#include "kernel/cvector.h"

#ifdef QT_AVAILABLE
class QImage;
#endif

class TrainingSample : public CVector
{
public:
    TrainingSample() {}
#ifdef QT_AVAILABLE
    TrainingSample(const QImage&);
#endif
};

#endif // TRAININGSAMPLE_H
