#include "MainWindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    MainWindow w;
    w.show();
#endif

    return a.exec();
}
