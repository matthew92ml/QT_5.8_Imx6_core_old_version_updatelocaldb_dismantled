#include "grdsplashmessage.h"

grdSplashMessage::grdSplashMessage(QWidget *parent) : QMainWindow(parent)
{
    mDataObject = new grdDataObject();

    baseText = "AGGIORNAMENTO DATI IN CORSO\nATTENDERE PREGO";
    int w = 1280;
    int h = 800;
    int fontsize = 40;
    int messageNRowsMax = 4;
    int messageh = fontsize*(messageNRowsMax+2);
    int messagey = (h-messageh)/2;
    this->setGeometry(0,0,w,h);
    message = new QLabel(this);
    message->setGeometry(0,messagey,w,messageh);
    message->setText(baseText);
    message->setAlignment(Qt::AlignCenter);
    message->setFont(QFont("Futura", fontsize, QFont::Bold));

    nTries = 0;
    currenStep = 0;
    timerExit = new QTimer(this);
    timerExit->setInterval(1000);  //1 secondo
    timerExit->setSingleShot(false);
    connect(timerExit, SIGNAL(timeout()),this, SLOT(tick()));

    timerExit->start();
}

grdSplashMessage::~grdSplashMessage(){
}

void grdSplashMessage::paintEvent(QPaintEvent *){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0.0, 0.0);
    painter.scale(1.0, 1.0);
}

void grdSplashMessage::tick(){
    int ret;

    switch (currenStep) {
    case 0:
        ret = mDataObject->updateDbLocal();
        if(ret == 0 || nTries > 2){
            //USCITA
            if(ret == 0)
                message->setText(QString(baseText).append("\n\nAGGIORNAMENTO TERMINATO"));
            else
                message->setText(QString(baseText).append("\n\nAGGIORNAMENTO FALLITO"));
            currenStep = 2;
        }
        else{
            //incremento i tentativi
            timeoutTimer.start();
            currenStep = 1;
            nTries++;
            message->setText(QString(baseText).append("\n\nTENTATIVO N.").append(QString::number(nTries)));
        }
        break;

    case 1:
        if(timeoutTimer.elapsed() > 1000){
            //attendo 1 secondo prima di riprovare
            currenStep = 0;
        }
        break;

    case 2:
        exit(ret);
        break;

    }



}
