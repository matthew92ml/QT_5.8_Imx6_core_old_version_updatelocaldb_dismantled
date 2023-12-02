#include "grddataobject.h"

grdDataObject::grdDataObject()
{
    loadParameters();
}

void grdDataObject::loadParameters() {

  QSettings settings("/home/user/ECOFILL/GRD/data/mp.data", QSettings::IniFormat);
  idComune = settings.value("GENERALE/IDCOMUNE", QString::number(idComune)).toInt();

  fileNameUtenti = QString("/home/user/ECOFILL/GRD/data/tag/tagutenti.tag");
  fileNameAdmin = QString("/home/user/ECOFILL/GRD/data/tag/tagadmin.tag");
  fileNameOp = QString("/home/user/ECOFILL/GRD/data/tag/tagop.tag");
  fileNameIspettori = QString("/home/user/ECOFILL/GRD/data/tag/tagispettori.tag");
  fileNameSpecial = QString("/home/user/ECOFILL/GRD/data/tag/tagspecial.tag");
  fileNameTesters = QString("/home/user/ECOFILL/GRD/data/tag/tagtesters.tag");
  fileNameManutentori= QString("/home/user/ECOFILL/GRD/data/tag/tagmanutentori.tag");

  //parametri database default
  dbDriver = "QPSQL";
  dbHostName = "127.0.0.1";
  dbPort = 5432;
  dbName = "grddb";
  sslRequired = "requiressl=1";
  dbUser = "grduser";
  dbPwd = "grduser2014";

  dbDriver = settings.value("DB/DRIVER", dbDriver).toString();
  dbHostName = settings.value("DB/HOSTNAME", dbHostName).toString();
  dbPort = settings.value("DB/PORT", QString::number(dbPort)).toInt();
  dbName = settings.value("DB/NAME", dbName).toString();
  dbUser = settings.value("DB/USER", dbUser).toString();
  dbPwd = settings.value("DB/PWD", dbPwd).toString();

  db = QSqlDatabase::addDatabase(dbDriver);
  db.setHostName(dbHostName);
  db.setPort(dbPort);
  db.setDatabaseName(dbName);
  db.setConnectOptions(sslRequired);
  db.setConnectOptions("connect_timeout = 60"); //10

  dbLocal = QSqlDatabase::addDatabase("QSQLITE","localConnection");
  dbLocal.setDatabaseName("/home/user/ECOFILL/GRD/data/grddb");

}

int grdDataObject::creaFileUtenti(QSqlQuery query, QString idComuneStr){
    int ret = 0;
    bool out = false;
    QString tag;
    int attivata;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag, attivata FROM infonuclei WHERE idcomune = " + idComuneStr);
    if(out){
            //crea il file locale
            QFile file(fileNameUtenti);
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamUtenti(&file);
                    mStreamUtenti << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           attivata = query.value(1).toInt();
                           mStreamUtenti << tag << "," << attivata <<  endl;
                    }
                    file.close();
                    statoFileUtenti = true;
            }
            else
                ret = -21;
    }

    return ret;
}

int grdDataObject::creaFileOperatori(QSqlQuery query, QString idComuneStr){
    int ret = 0;
    bool out = false;
    QString tag;
    int unlock, livello;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag, unlock, livello FROM infooperatori WHERE idcomune = " + idComuneStr);
    if(out){
            //crea il file locale
            QFile fileOp(fileNameOp);
            if(fileOp.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamOp(&fileOp);
                    mStreamOp << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           unlock = query.value(1).toInt();
                           livello = query.value(2).toInt();
                           mStreamOp << tag << "," << unlock << "," << livello << endl;
                    }
                    fileOp.close();
                    statoFileOperatori=true;
            }
            else
                ret = -22;
    }

    return ret;
}

int grdDataObject::creaFileAmministratori(QSqlQuery query){
    int ret = 0;
    bool out = false;
    QString tag;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag FROM infoamministratori");
    if(out){
            //crea il file locale
            QFile fileAdmin(fileNameAdmin);
            if(fileAdmin.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamAdmin(&fileAdmin);
                    mStreamAdmin << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           mStreamAdmin << tag << endl;
                    }
                    fileAdmin.close();
                    statoFileAmministratori=true;
            }
            else
                ret = -23;
    }
    return ret;
}

int grdDataObject::creaFileUtentiSpeciali(QSqlQuery query, QString idComuneStr){
    int ret = 0;
    bool out = false;
    QString tag;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag FROM specialusers WHERE idcomune = " + idComuneStr);
    if(out){
            //crea il file locale
            QFile fileSpecial(fileNameSpecial);
            if(fileSpecial.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamSpecial(&fileSpecial);
                    mStreamSpecial << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           mStreamSpecial << tag << endl;
                    }
                    fileSpecial.close();
                    statoFileUtentiSpeciali=true;
            }
            else
                ret = -24;
    }

    return ret;
}

int grdDataObject::creaFileTesters(QSqlQuery query){
    int ret = 0;
    bool out = false;
    QString tag;
    int skipWeight;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag,skipweight FROM infotesters");
    if(out){
            //crea il file locale
            QFile fileTesters(fileNameTesters);
            if(fileTesters.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamTesters(&fileTesters);
                    mStreamTesters << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           skipWeight = query.value(1).toInt();
                           mStreamTesters << tag << "," << skipWeight << endl;
                    }
                    fileTesters.close();
                    statoFileTesters=true;
            }
            else
                ret = -25;
    }

    return ret;
}

int grdDataObject::creaFileManutentori(QSqlQuery query, QString idComuneStr){
    int ret = 0;
    bool out = false;
    QString tag;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag FROM infomanutentori WHERE idcomune = " + idComuneStr);
    if(out){
            //crea il file locale
            QFile fileManutentori(fileNameManutentori);
            if(fileManutentori.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamManutentori(&fileManutentori);
                    mStreamManutentori << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           mStreamManutentori << tag << endl;
                    }
                    fileManutentori.close();
                    statoFileManutentori=true;
            }
            else
                ret = -25;
    }

    return ret;
}

int grdDataObject::creaFileIspettori(QSqlQuery query, QString idComuneStr){
    int ret = 0;
    bool out = false;
    QString tag;

    QString dataOra = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out = query.exec("SELECT codicetag FROM infoispettori WHERE idcomune = " + idComuneStr);
    if(out){
            //crea il file locale
            QFile fileIspetttori(fileNameIspettori);
            if(fileIspetttori.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream mStreamIspettori(&fileIspetttori);
                    mStreamIspettori << dataOra << endl;
                    while(query.next()){
                           tag = query.value(0).toString();
                           mStreamIspettori << tag << endl;
                    }
                    fileIspetttori.close();
                    statoFileIspettori=true;
            }
            else
                ret = -25;
    }
    return ret;
}

int grdDataObject::getTagFromRemoteDB(){
    //appoggia le tag prelevate dal db remoto su dei file
    int ret = 0;
    QString idComuneStr = QString::number(idComune);

    QString localFolder = "/home/user/ECOFILL/GRD/data/tag/";
    //crea la cartella locale se non esiste
    if(!QDir(localFolder).exists()){
        QDir().mkpath(localFolder);
    }

     statoFileUtenti= false;
     statoFileOperatori= false;
     statoFileAmministratori= false;
     statoFileManutentori= false;
     statoFileTesters= false;
     statoFileIspettori= false;
     statoFileUtentiSpeciali= false;

    if(db.open(dbUser,dbPwd)){
        QSqlQuery query(db);
        ret = creaFileUtenti(query,idComuneStr);
        ret = creaFileOperatori(query,idComuneStr);
        ret = creaFileAmministratori(query);
        ret = creaFileUtentiSpeciali(query,idComuneStr);
        ret = creaFileTesters(query);
        ret = creaFileManutentori(query,idComuneStr);
        ret = creaFileIspettori(query,idComuneStr);
    }
    else{
        qDebug() << QString("db.open:%1").arg(db.lastError().text());
        ret = -1;
    }

    return ret;
}

int grdDataObject::pulisciDb(QSqlQuery query,QString tableName){
    int ret = 0;
    QString queryTxt;
    queryTxt = QString("DELETE FROM ").append(tableName);
    if(!query.exec(queryTxt)){
        qDebug() << QString("pulisciDb:%1").arg(query.lastError().text());
        ret = -2;
    }
    return ret;
}

int grdDataObject::leggiFileUtenti(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString attivata;
    QString queryTxt;
    QFile file(fileNameUtenti);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStream(&file);
        mStream.readLine(); //leggo la data
        while(!mStream.atEnd()){
            QStringList tagAndAttivata  = mStream.readLine().split(",");
            if(tagAndAttivata.length()>1){
                tag = tagAndAttivata[0];
                attivata = tagAndAttivata[1];
            }
            queryTxt = QString("INSERT INTO infonuclei(codicetag, attivata) VALUES('").append(tag).append("',").append(attivata).append(")");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal nuclei:%1").arg(query.lastError().text());
                ret = -2;
            }
        }
    }
    file.close();

    return ret;
}

int grdDataObject::leggiFileOperatori(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString unlock;
    QString livello;
    QString queryTxt;
    QFile fileOp(fileNameOp);
    if(fileOp.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamOp(&fileOp);
        mStreamOp.readLine(); //leggo la data
        while(!mStreamOp.atEnd()){
            QString tagAndUnlockAndLivello  = mStreamOp.readLine();
            QStringList tagAndUnlockAndLivelloSplitted = tagAndUnlockAndLivello.split(",");
            if(tagAndUnlockAndLivelloSplitted.length()>1){
                tag = tagAndUnlockAndLivelloSplitted[0];
                unlock = tagAndUnlockAndLivelloSplitted[1];
                livello = tagAndUnlockAndLivelloSplitted[2];
            }
            queryTxt = QString("INSERT INTO infooperatori(codicetag, unlock, livello) VALUES('").append(tag).append("',").append(unlock).append(",").append(livello).append(")");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal op:%1").arg(query.lastError().text());
                ret = -3;
            }
        }
    }
    fileOp.close();

    return ret;
}

int grdDataObject::leggiFileAmministratori(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString queryTxt;
    QFile fileAdmin(fileNameAdmin);
    if(fileAdmin.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamAdmin(&fileAdmin);
        mStreamAdmin.readLine(); //leggo la data
        while(!mStreamAdmin.atEnd()){
            tag  = mStreamAdmin.readLine();
            queryTxt = QString("INSERT INTO infoamministratori(codicetag) VALUES('").append(tag).append("')");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal admin:%1").arg(query.lastError().text());
                ret = -4;
            }
        }
    }
    fileAdmin.close();

    return ret;
}

int grdDataObject::leggiFileManutentori(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString queryTxt;

    QFile fileManutentori(fileNameManutentori);
    if(fileManutentori.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamManutentori(&fileManutentori);
        mStreamManutentori.readLine(); //leggo la data
        while(!mStreamManutentori.atEnd()){
            tag  = mStreamManutentori.readLine();
            queryTxt = QString("INSERT INTO infomanutentori(codicetag) VALUES('").append(tag).append("')");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal manutentori:%1").arg(query.lastError().text());
                ret = -4;
            }
        }
    }
    fileManutentori.close();

    return ret;
}

int grdDataObject::leggiFileTesters(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString skipWeight;
    QString queryTxt;

    QFile fileTesters(fileNameTesters);
    if(fileTesters.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamTesters(&fileTesters);
        mStreamTesters.readLine(); //leggo la data
        while(!mStreamTesters.atEnd()){
            QString tagAndSkipWeight  = mStreamTesters.readLine();
            QStringList tagAndSkipWeightSplitted = tagAndSkipWeight.split(",");
            if(tagAndSkipWeightSplitted.length()>1){
                tag = tagAndSkipWeightSplitted[0];
                skipWeight = tagAndSkipWeightSplitted[1];
            }

            queryTxt = QString("INSERT INTO infotesters(codicetag,skipweight) VALUES('").append(tag).append("',").append(skipWeight).append(")");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal testers:%1").arg(query.lastError().text());
                ret = -6;
            }
        }
    }
    fileTesters.close();

    return ret;
}

int grdDataObject::leggiFileIspettori(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString queryTxt;

    QFile fileIspettori(fileNameIspettori);
    if(fileIspettori.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamIspettori(&fileIspettori);
        mStreamIspettori.readLine(); //leggo la data
        while(!mStreamIspettori.atEnd()){
            tag  = mStreamIspettori.readLine();
            queryTxt = QString("INSERT INTO infoispettori(codicetag) VALUES('").append(tag).append("')");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal infoispettori:%1").arg(query.lastError().text());
                ret = -7;
            }
        }
    }
    fileIspettori.close();

    return ret;
}

int grdDataObject::leggiFileUtentiSpeciali(QSqlQuery query){
    int ret = 0;
    QString tag;
    QString queryTxt;
    QFile fileSpecial(fileNameSpecial);
    if(fileSpecial.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream mStreamSpecial(&fileSpecial);
        mStreamSpecial.readLine(); //leggo la data
        while(!mStreamSpecial.atEnd()){
            tag  = mStreamSpecial.readLine();
            queryTxt = QString("INSERT INTO specialusers(codicetag) VALUES('").append(tag).append("')");
            if(!query.exec(queryTxt)){
                qDebug() << QString("updateDbLocal special:%1").arg(query.lastError().text());
                ret = -5;
            }
        }
    }
    fileSpecial.close();
    return ret;
}

int grdDataObject::updateDbLocal(){
    //legge i file di appoggio e salva le tag su db locale
    int ret = 0;

    if(getTagFromRemoteDB()!=-1)
    {
        if(dbLocal.open(dbUser,dbPwd)){
            QSqlQuery query(dbLocal);
            if(statoFileUtenti){
                pulisciDb(query,"infonuclei");
                leggiFileUtenti(query);
            }
            if(statoFileOperatori){
                pulisciDb(query,"infooperatori");
                leggiFileOperatori(query);
            }
            if(statoFileIspettori){
                pulisciDb(query,"infoispettori");
                leggiFileIspettori(query);
            }
            if(statoFileAmministratori){
                pulisciDb(query,"infoamministratori");
                leggiFileAmministratori(query);
            }
            if(statoFileUtentiSpeciali){
                pulisciDb(query,"specialusers");
                leggiFileUtentiSpeciali(query);
            }
            if(statoFileTesters){
                pulisciDb(query,"infotesters");
                leggiFileTesters(query);
            }
            if(statoFileManutentori){
                pulisciDb(query,"infomanutentori");
                leggiFileManutentori(query);
            }
            dbLocal.close();
        }
        else{
            lastError = dbLocal.lastError().text();
            //Singleton<grdLogger>::Instance().writeLog(QString("updateDbLocal:%1").arg(lastError),"ERR/UPDATE_TAG");
            qDebug() << QString("updateDbLocal:%1").arg(lastError);
            ret = -1;
        }

    }
    else
        ret = -2;

    return ret;
}
