#include "QThreadt.h"

QThreadt::QThreadt(QString s,QString b)
{
	sql = s;
	db.addconection(b);

}

void QThreadt::run()
{
	QStringList result;
	QSqlQuery query = db.querysql(sql);
	while (query.next())
	{
		QString x = query.value(0).toString() + "\t" + query.value(1).toString() + "\t" + query.value(2).toString();
		result.append(x);
	}
	emit sendtable(result);
}
