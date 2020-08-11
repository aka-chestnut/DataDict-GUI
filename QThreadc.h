#pragma once
#include <qthread.h>
#include <DataBase.h>
class QThreadc :
    public QThread
{
	Q_OBJECT
public:
	QThreadc(QString s,QString b);
	void run();
	QString sql;

private:
	DataBase db;
signals:
	void sendcol(QStringList s);
};

