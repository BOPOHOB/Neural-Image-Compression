#ifndef FRAMEGRIDDISPLAY_H
#define FRAMEGRIDDISPLAY_H

#ifdef QT_AVAILABLE
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

    static QSize frameSize(const QSize& imgSize, const QSize& gridSize);

public slots:
    void enableGreed(const bool);

private:
    QSize gridSize;
    QList<QImage> frameList;
    bool isGreed;
};

#endif
#endif // FRAMEGRIDDISPLAY_H
