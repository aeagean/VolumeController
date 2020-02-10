#include "MainWindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit("VolumeController by Qt君"));
    w.show();

    return a.exec();
}
