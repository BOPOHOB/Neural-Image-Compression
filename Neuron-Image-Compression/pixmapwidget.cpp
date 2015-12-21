#ifdef QT_AVAILABLE
#include "pixmapwidget.h"

#include <QImage>
#include <QPixmap>
#include <QPaintDevice>
#include <QPainter>
#include <QDebug>

PixmapWidget::PixmapWidget(QWidget *parent)
    : QWidget(parent)
{
}
PixmapWidget::PixmapWidget(const QPixmap& img, QWidget* parent)
    : QWidget(parent)
    , __img(img)
{
}

PixmapWidget::~PixmapWidget()
{

}


void PixmapWidget::paintEvent(QPaintEvent * e) {
    if (__img.isNull()) {
        QWidget::paintEvent(e);
    } else {
        QPainter(this).drawPixmap(0,0, __img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}
void PixmapWidget::setImage(const QImage& i) { __img.convertFromImage(i); }
void PixmapWidget::setPixmap(const QPixmap& p) { __img = p; }
const QPixmap& PixmapWidget::pixmap() const { return __img; }
#endif
