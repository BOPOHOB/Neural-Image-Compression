#include "mainwidget.h"
#include <QApplication>
#include "kernel/carray.h"
#include "kernel/cvector.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f("test");

    for (int i(0); i != 0x10; ++i) {
        CVector array(i);
        for (int j(0); j != static_cast<int>(array.size()); ++j) {
            array[j] = rand() * 1.0 / RAND_MAX;
        }
        f.open(QFile::WriteOnly);
        QDataStream out(&f);
        out << array;
        f.close();
        f.open(QFile::ReadOnly);
        QDataStream in(&f);
        CArray enotherArray;
        in >> enotherArray;
        qDebug() << array << '\n' << enotherArray;
        if (array != enotherArray) {
            qFatal("arrays not equal");
        }
        f.close();
    }
    a.quit();
    return 0;


    MainWidget w;
    w.show();
    return a.exec();
}
