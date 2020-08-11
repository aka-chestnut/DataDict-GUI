
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
    bool createConnection(QString);  //创建一个连接

    bool createConnection2(QString s);

    bool queryAll();          //查询所有信息
                       
    bool sortById();          //排序
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
