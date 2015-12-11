#include "trainingsample.h"
#ifdef QT_AVAILABLE
#include <QImage>
#include <QRgb>
#endif

#ifdef QT_AVAILABLE
TrainingSample::TrainingSample(const QImage& img)
    : CVector(img.width() * img.height(), 0.0, CVector::Vertical)
{
    for (int i(0); i != img.height(); ++i) {
        for (int j(0); j != img.width(); ++j) {
            this->at(i * img.width() + j) = qGray(img.pixel(j, i));
        }
    }
}
#endif
