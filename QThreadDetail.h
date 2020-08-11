#include <QThread>
#include "DataBase.h"
class QThreadDetail:public QThread
{
	Q_OBJECT
public:
	QThreadDetail(QString s, QString b);


	void run();
	QString sql;

private:
	DataBase db;
signals:
	void senddetails(QStringList s);
};

