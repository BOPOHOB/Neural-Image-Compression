#include "framegriddisplay.h"

#ifdef QT_AVAILABLE
#include <QGridLayout>
#include <QPixmap>
#include <QPainter>

#include <QDebug>
#include "pixmapwidget.h"

FrameGridDisplay::FrameGridDisplay(QWidget *parent) : QWidget(parent), isGreed(true)
{
}

FrameGridDisplay::~FrameGridDisplay()
{

}

void FrameGridDisplay::paintEvent(QPaintEvent *)
{
    if (frameList.size() != gridSize.width() * gridSize.height()) {
        return;
    }
    QPainter p(this);
    const QSize frameSize(frameList.first().size());
    for (int i(0); i != gridSize.width(); ++i) {
        for (int j(0); j != gridSize.height(); ++j) {
            p.drawImage((isGreed + frameSize.width()) * i,
                        (isGreed + frameSize.height()) * j,
                        frameList.at(i * gridSize.height() + j));
        }
    }
}

QSize FrameGridDisplay::frameSize(const QSize& img, const QSize& gridSize)
{
    return QSize(img.width() / gridSize.width(),
                 img.height() / gridSize.height());
}

void FrameGridDisplay::setPixmap(const QPixmap& img, const QSize& gridSize)
{
    frameList.clear();
    this->gridSize = gridSize;
    const QSize frameSize(FrameGridDisplay::frameSize(img.size(), gridSize));
    for (int i(0); i != gridSize.width(); ++i) {
        for (int j(0); j != gridSize.height(); ++j) {
            QImage p(frameSize, QImage::Format_RGB888);
            QPainter peinter(&p);
            peinter.drawPixmap(frameSize.width() * -i,
                               frameSize.height() * -j,
                               img);
            frameList << p;
        }
    }
    this->setMinimumSize((frameSize.width() + 1) * gridSize.width() - 1,
                         (frameSize.height() + 1) * gridSize.height() - 1);
}

const QList<QImage>& FrameGridDisplay::getFrameList() const
{
    return frameList;
}

void FrameGridDisplay::enableGreed(const bool v)
{
    isGreed = v;
    this->update();
}
#endif
