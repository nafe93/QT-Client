#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    w.createMatrix();
    w.createFireMatrix();
    w.creatShip();
    w.drawingYourLife();

    w.drawing();
    w.drawingFire();

    return a.exec();
}
