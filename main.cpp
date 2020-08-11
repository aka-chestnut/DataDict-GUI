#include "AutoHideWidget.h"
#include <QApplication>
#include "DataBase.h"
#include "SplashScreen.h"
#include "DataBasem.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SplashScreen splash(QPixmap("splash.jpg"));
    splash.show();
    a.processEvents();
    DataBasem dbt;
    QObject::connect(&dbt, SIGNAL(startReadData(int, QString)),
        &splash, SLOT(showProgressMessage(int, QString))
    );
    QObject::connect(&dbt, SIGNAL(readingData(int)),
        &splash, SLOT(updateProgress(int))
    );
    dbt.readData();


    AutoHideWidget w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
