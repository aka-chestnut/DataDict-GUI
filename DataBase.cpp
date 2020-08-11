#include "DataBase.h"
//建立一个数据库连接
bool DataBase::createConnection(QString s)
{
    
    //以后就可以用connection_name与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    db.setDatabaseName(".//qtDb.db");
    if (!db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    queryColSource();
    queryTableSource();
    return true;

}

bool DataBase::createConnection2(QString s)
{

    //以后就可以用connection_name与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    db.setDatabaseName(".//qtDb.db");


    return true;

}


//创建数据库表



//查询所有信息
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database(connection_name); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from automobil");
    QSqlRecord rec = query.record();
    return true;
   
}




//排序
bool DataBase::sortById()
{
    QSqlDatabase db = QSqlDatabase::database(connection_name); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("select * from automobil order by id desc");
    if (success)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void DataBase::queryTableSource()
{
    QSqlDatabase db = QSqlDatabase::database(connection_name); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select distinct db_name from table_info order by db_name");
    QSqlRecord rec = query.record();
    //qDebug() << QObject::tr("automobil表字段数：") << rec.count();

    while (query.next())
    {
        v_tableSource.append(query.value(0).toString());
    }
    v_tableSource.append(QString("ALL"));
}

void DataBase::queryColSource()
{
    QSqlDatabase db = QSqlDatabase::database(connection_name); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select distinct upper(hive_db) from col_info order by hive_db");
    QSqlRecord rec = query.record();
    //qDebug() << QObject::tr("automobil表字段数：") << rec.count();

    while (query.next())
    {
        v_colSource.append(query.value(0).toString());
    }
    v_colSource.append(QString("ALL"));

}

void DataBase::addconection(QString s)
{
    connection_name = s;
}

QSqlQuery DataBase::querysql(QString a)
{
    createConnection2(connection_name);
    QSqlDatabase db = QSqlDatabase::database(connection_name); //建立数据库连接
    QSqlQuery query(db);
    query.exec(a);
    return query;
}
