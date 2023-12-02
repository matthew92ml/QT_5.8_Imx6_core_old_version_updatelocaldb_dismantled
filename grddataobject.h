#ifndef GRDDATAOBJECT_H
#define GRDDATAOBJECT_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QSettings>

class grdDataObject
{
public:
    grdDataObject();

public:
    int updateDbLocal();

private:
    void loadParameters();
    int getTagFromRemoteDB();
    int pulisciDb(QSqlQuery query,QString tableName);
    int creaFileUtenti(QSqlQuery query, QString idComuneStr);
    int creaFileOperatori(QSqlQuery query, QString idComuneStr);
    int creaFileAmministratori(QSqlQuery query);
    int creaFileManutentori(QSqlQuery query, QString idComuneStr);
    int creaFileTesters(QSqlQuery query);
    int creaFileIspettori(QSqlQuery query, QString idComuneStr);
    int creaFileUtentiSpeciali(QSqlQuery query, QString idComuneStr);

    int leggiFileUtenti(QSqlQuery query);
    int leggiFileOperatori(QSqlQuery query);
    int leggiFileAmministratori(QSqlQuery query);
    int leggiFileManutentori(QSqlQuery query);
    int leggiFileTesters(QSqlQuery query);
    int leggiFileIspettori(QSqlQuery query);
    int leggiFileUtentiSpeciali(QSqlQuery query);

    bool statoFileUtenti;
    bool statoFileOperatori;
    bool statoFileAmministratori;
    bool statoFileManutentori;
    bool statoFileTesters;
    bool statoFileIspettori;
    bool statoFileUtentiSpeciali;

    int idComune;

     QSqlDatabase db;
     QSqlDatabase dbLocal;

     QString dbDriver;
     QString dbHostName;
     int dbPort;
     QString dbName;
     QString sslRequired;

     QString dbUser;
     QString dbPwd;
     QString lastError;

     QString fileNameUtenti;
     QString fileNameAdmin;
     QString fileNameOp;
     QString fileNameIspettori;
     QString fileNameTesters;
     QString fileNameSpecial;
     QString fileNameManutentori;

};

#endif // GRDDATAOBJECT_H
