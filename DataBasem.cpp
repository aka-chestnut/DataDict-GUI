#include "DataBasem.h"
DataBasem::DataBasem(QObject* parent) : QObject(parent) {
}

void DataBasem::readData() {
    int max = 1500;
    emit startReadData(max, QStringLiteral("KDataDict v2.1 Coding The World. ȫ�°汾��ȫ������.  "));
    for (int i = 0; i < max; ++i) {
        emit this->readingData(i);
        qDebug("reading data");
    }
}

