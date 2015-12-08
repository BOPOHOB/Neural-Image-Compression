#include "trainingsample.h"
#ifdef QT_AVAILABLE
#include <QImage>
#endif

TrainingSample::TrainingSample()
{

}

#ifdef QT_AVAILABLE
TrainingSample::TrainingSample(const QImage& img)
    : std::vector<char>(img.width() * img.height())
{
    for (int i(0); i != img.height(); ++i) {
        for (int j(0); j != img.width(); ++j) {
            this->at(i * img.height() + j) = img.pixel(i, j);
        }
    }
}
#endif
