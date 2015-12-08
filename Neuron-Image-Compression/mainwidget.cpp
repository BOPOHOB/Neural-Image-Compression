#include "mainwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QProgressBar>
#include <QSpinBox>
#include <QFileDialog>
#include <QPainter>
#include <QRadioButton>
#ifdef Q_OS_WIN
#include <QtWinExtras>
#endif
#include <QDebug>

#include "filenameedit.h"
#include "pixmapwidget.h"
#include "kernel/csize.h"
#include "framegriddisplay.h"
#include "neuralcompressor.h"
#include "trainingset.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , progress(new QProgressBar(this))
    , initial(new FrameGridDisplay(this))
    , result(new PixmapWidget(this))
    , input(new FileNameEdit(this))
    , clipWidthSpin(new QSpinBox(this))
    , clipHeightSpin(new QSpinBox(this))
    , frameWidthSpin(new QSpinBox(this))
    , frameHeightSpin(new QSpinBox(this))
    , lSpin(new QSpinBox(this))
    , currentMode(Cut)
{
#ifdef Q_OS_WIN
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);
        setStyleSheet("MainWidget { background: transparent; }");
    }
#endif

    this->setLayout(new QVBoxLayout);

    input->setOpenFileFunction([](FileNameEdit*)->QString{
        return QFileDialog::getOpenFileName(0, tr("Chose file"), "", "*.png *.gif *.jpg");
    });

    this->layout()->addWidget(input);
    QHBoxLayout* const l(new QHBoxLayout);
    static_cast<QVBoxLayout*>(this->layout())->addLayout(l);
    static_cast<QVBoxLayout*>(this->layout())->addStretch();
    this->layout()->addWidget(progress);

    l->addWidget(initial);
    QFormLayout* params(new QFormLayout);
    l->addLayout(params);
    l->addWidget(result);

    clipWidthSpin->setValue(256);
    clipHeightSpin->setValue(256);
    frameWidthSpin->setValue(16);
    frameHeightSpin->setValue(16);
    clipWidthSpin->setMinimum(1);
    clipHeightSpin->setMinimum(1);
    frameWidthSpin->setMinimum(1);
    frameHeightSpin->setMinimum(1);
    lSpin->setValue(64);
    params->addRow(tr("Clip width"), clipWidthSpin);
    params->addRow(tr("Clip height"), clipHeightSpin);
    params->addRow(tr("Resize mode"), ([this]()->QWidget*{
        QWidget* const radio(new QWidget(this));
        QRadioButton* const cut(new QRadioButton(tr("Cut"), radio));
        cut->setChecked(true);
        QRadioButton* const scale(new QRadioButton(tr("Scale"), radio));
        radio->setLayout(new QVBoxLayout);
        radio->layout()->addWidget(cut);
        radio->layout()->addWidget(scale);
        this->connect(cut, SIGNAL(clicked()), this, SLOT(setCutResizeMode()));
        this->connect(scale, SIGNAL(clicked()), this, SLOT(setScaleResizeMode()));
        return radio;
    })());
    params->addRow(tr("Frame grid columns count"), frameWidthSpin);
    params->addRow(tr("Frame grid rows count"), frameHeightSpin);
    params->addRow(tr("L"), lSpin);

    this->connect(input, SIGNAL(fileNameChanged(QString)), SLOT(setFilename(QString)));
    this->connect(clipWidthSpin, SIGNAL(valueChanged(int)), SLOT(updateClipSize()));
    this->connect(clipHeightSpin, SIGNAL(valueChanged(int)), SLOT(updateClipSize()));
    this->connect(frameWidthSpin, SIGNAL(valueChanged(int)), SLOT(updateFrameSize()));
    this->connect(frameHeightSpin, SIGNAL(valueChanged(int)), SLOT(updateFrameSize()));
    this->connect(lSpin, SIGNAL(valueChanged(int)), SLOT(update()));
}

void MainWidget::setCutResizeMode()
{
    currentMode = Cut;
    update();
}

void MainWidget::setScaleResizeMode()
{
    currentMode = Scale;
    update();
}

void MainWidget::setFilename(const QString& f)
{
    source = QImage(f);
    for (int i(0); i != source.width(); ++i) {
        for (int j(0); j != source.height(); ++j) {
            const int gray(qGray(source.pixel(i, j)));
            source.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    clipWidthSpin->setMaximum(source.width());
    clipHeightSpin->setMaximum(source.height());
    clipWidthSpin->setValue(256);
    clipHeightSpin->setValue(256);
    update();
}

void MainWidget::updateFrameSize()
{
    update();
    if (!initial->getFrameList().empty()) {
        const QSize s(initial->getFrameList().first().size());
        lSpin->setMaximum(s.width() * s.height());
    }
}

void MainWidget::updateClipSize()
{
    frameWidthSpin->setMaximum(clipWidthSpin->value());
    frameHeightSpin->setMaximum(clipHeightSpin->value());
    update();
}

void MainWidget::update()
{
    QPixmap pix(clipWidthSpin->value(), clipHeightSpin->value());
    QPainter p(&pix);
    if (currentMode == Scale) {
        p.drawImage(0, 0, source.scaled(clipWidthSpin->value(), clipHeightSpin->value()));
    } else {
        p.drawImage((clipWidthSpin->value() - source.width()) >> 1,
                    (clipHeightSpin->value() - source.height()) >> 1,
                    source);
    }
    initial->setPixmap(pix, QSize(frameWidthSpin->value(), frameHeightSpin->value()));
    initial->update();

    result->setPixmap(NeuralCompressor(TrainingSet(initial->getFrameList())).recoverToQPixmap());
}

MainWidget::~MainWidget()
{

}
