#include "QThreadc.h"

QThreadc::QThreadc(QString s,QString b)
{
	sql = s;
	db.addconection(b);

}

void QThreadc::run()
{
	QStringList result;
	QSqlQuery query = db.querysql(sql);
	while (query.next())
	{
		QString x = query.value(0).toString() +"\t"+ query.value(1).toString() + "\t"+ query.value(2).toString() + "\t"+ query.value(3).toString();
		result.append(x);
	}
	emit sendcol(result);
}
