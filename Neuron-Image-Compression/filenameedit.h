#ifndef FILENAMEEDIT_H
#define FILENAMEEDIT_H

#include <QLineEdit>
#ifdef _WIN32
# include <functional>
using std::function;
#else
# include <tr1/functional>
using std::tr1::function;
#endif

class QPushButton;
class QFileDialog;

class FileNameEdit : public QLineEdit {
    Q_OBJECT

private:
    void resizeEvent(QResizeEvent *);
    bool eventFilter(QObject *, QEvent *);

public:
    FileNameEdit(QWidget* parent = 0);
    void setOpenFileFunction(function<QString(FileNameEdit*)> f) { __onClick = f; }

signals:
    void fileNameChanged(QString);
private slots:
    void callDialod();
    void valueTest();

private:
    QPushButton* const __pb;
    QWidget* const __warning;
    function<QString(FileNameEdit*)> __onClick;
};


#endif // FILENAMEEDIT_H
