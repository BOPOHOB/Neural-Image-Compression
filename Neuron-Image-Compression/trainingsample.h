#ifndef TRAININGSAMPLE_H
#define TRAININGSAMPLE_H

#include <vector>

#ifdef QT_AVAILABLE
class QImage;
#endif

class TrainingSample : std::vector<char>
{
public:
    TrainingSample();
#ifdef QT_AVAILABLE
    TrainingSample(const QImage&);
#endif
};

#endif // TRAININGSAMPLE_H
