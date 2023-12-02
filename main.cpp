#include <QtGui>
#include <QApplication>
#include <QDebug>
#include "grdsplashmessage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "updateDbLocal v10.0.0b (24/09/2019)";

    grdSplashMessage m;
    m.show();
    return a.exec();
}
