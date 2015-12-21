#ifndef QT_AVAILABLE
#include <iostream>
#include "trainingset.h"
#include "kernel/csize.h"
#include "neuralcompressor.h"

int main(int argc, char* argv[])
{
#ifdef ENABLE_PNG
    const char* sourceFile(argc == 2 ? argv[1] : "nn3.png");
    TrainingSet src(sourceFile, 128, 128);
    NeuralCompressor(src, 32, CSize(2,2), CSize(255,255)).saveAs("freak22.png", sourceFile);
#else
    std::cerr << "I can't compress anything" << std::endl;
    return -1;
#endif
}
#else
#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.show();

    return a.exec();
}
#endif
