#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "pixmapwidget.h"

class QProgressBar;
class PixmapWidget;
class QSpinBox;
class FileNameEdit;
class FrameGridDisplay;

class MainWidget : public QWidget
{
    Q_OBJECT

    enum ResizeMode {
        Scale,
        Cut
    };

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void setFilename(const QString&);
    void setCutResizeMode();
    void setScaleResizeMode();
    void update();
    void updateClipSize();

private:
    QProgressBar* const progress;
    FrameGridDisplay* const initial;
    PixmapWidget* const result;
    FileNameEdit* const input;
    QSpinBox* const clipWidthSpin;
    QSpinBox* const clipHeightSpin;
    QSpinBox* const frameWidthSpin;
    QSpinBox* const frameHeightSpin;
    ResizeMode currentMode;

    QImage source;
};

#endif // MAINWIDGET_H
