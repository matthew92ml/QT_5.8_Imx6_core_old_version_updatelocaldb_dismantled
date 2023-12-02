#ifndef GRDSPLASHMESSAGE_H
#define GRDSPLASHMESSAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QLabel>

#include "grddataobject.h"


class grdSplashMessage : public QMainWindow
{
    Q_OBJECT
public:
    explicit grdSplashMessage(QWidget *parent = nullptr);
    ~grdSplashMessage();

private:
    const QPixmap *background;
    grdDataObject* mDataObject;
    QTimer *timerExit;
    QTime timeoutTimer;
    int nTries, currenStep;
    QLabel* message;
    QString baseText;

signals:

public slots:
    void tick();


protected:
   void paintEvent (QPaintEvent *);

};

#endif // GRDSPLASHMESSAGE_H
