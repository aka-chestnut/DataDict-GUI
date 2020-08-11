
#include <QThread>
#include "DataBase.h"
class QThreadt :public QThread
{
	Q_OBJECT
public:
	QThreadt(QString s,QString b);
	void run();
	QString sql;

private:
	DataBase db;
signals:
	void sendtable(QStringList s);
};

