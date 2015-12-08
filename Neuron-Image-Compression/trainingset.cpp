#include "trainingset.h"
#include <QImage>

TrainingSet::TrainingSet()
{

}


#ifdef QT_AVAILABLE
TrainingSet::TrainingSet(const QList<QImage>& l)
{
    this->reserve(l.size());
    for (const QImage& i : l) {
        this->push_back(i);
    }
}
#endif
