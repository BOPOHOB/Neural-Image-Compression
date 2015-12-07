#include "framegriddisplay.h"

#include <QGridLayout>
#include <QPixmap>
#include <QPainter>

#include <QDebug>
#include "pixmapwidget.h"

FrameGridDisplay::FrameGridDisplay(QWidget *parent) : QWidget(parent)
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
            p.drawImage((1 + frameSize.width()) * i,
                        (1 + frameSize.height()) * j,
                        frameList.at(i * gridSize.height() + j));
        }
    }
}

void FrameGridDisplay::setPixmap(const QPixmap& img, const QSize& gridSize)
{
    frameList.clear();
    this->gridSize = gridSize;
    const QSize frameSize(img.width() / gridSize.width(),
                          img.height() / gridSize.height());
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
