
#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <string>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QString>
using namespace std;
class DataBase
{

public:
    bool createConnection(QString);  //����һ������

    bool createConnection2(QString s);

    bool queryAll();          //��ѯ������Ϣ
                       
    bool sortById();          //����
    void queryTableSource();
    void queryColSource();
    void addconection(QString s);
    QSqlQuery querysql(QString a);
    QString connection_name;
public:
    QStringList v_tableSource;
    QStringList v_colSource;
    

};

#endif // DATABASE_H
