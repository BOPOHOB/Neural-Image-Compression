#ifndef FRAMEGRIDDISPLAY_H
#define FRAMEGRIDDISPLAY_H

#include <QWidget>

class QGridLayout;

class FrameGridDisplay : public QWidget
{
    Q_OBJECT

    void paintEvent(QPaintEvent *);
public:
    explicit FrameGridDisplay(QWidget *parent = 0);
    ~FrameGridDisplay();

    void setPixmap(const QPixmap& img, const QSize& gridSize);
    const QList<QImage>& getFrameList() const;

private:
    QSize gridSize;
    QList<QImage> frameList;
};

#endif // FRAMEGRIDDISPLAY_H
