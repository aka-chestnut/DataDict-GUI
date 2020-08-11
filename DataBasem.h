#ifndef  DATABASEM_H 
#define  DATABASEM_H  
#include   < QObject > 
#include   < QColor >  
class   DataBasem : public   QObject {
    Q_OBJECT
public:
    explicit   DataBasem(QObject* parent = 0);
    void  readData();
signals:
    void  readingData(int  num);
    void  startReadData(int  total, const   QString& msg);
};

#endif   // DATABASEM_H
