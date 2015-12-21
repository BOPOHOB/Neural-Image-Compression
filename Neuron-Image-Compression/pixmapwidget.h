#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#ifdef QT_AVAILABLE

#include <QWidget>

class PixmapWidget : public QWidget
{
    void paintEvent(QPaintEvent *);
public:

    explicit PixmapWidget(QWidget *parent = 0);
    PixmapWidget(const QPixmap& img, QWidget* parent = 0);
    ~PixmapWidget();

    void setImage(const QImage&);
    void setPixmap(const QPixmap&);
    const QPixmap& pixmap() const;

private:
    QPixmap __img;
};

#endif
#endif // ICONWIDGET_H
