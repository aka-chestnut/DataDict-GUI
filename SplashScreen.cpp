#include <QProgressBar>
#include "SplashScreen.h"

SplashScreen::SplashScreen(QPixmap pixmap, QWidget* parent) :
    QSplashScreen(parent, pixmap)
{

    bar = new QProgressBar(this);
    //设置进度条的位置    
    bar->setGeometry(0, pixmap.height() - 50, pixmap.width(), 30);
    resize(pixmap.size());
}

SplashScreen::~SplashScreen() {
}

void SplashScreen::setRange(int min, int max) {
    bar->setRange(min, max);
}

void SplashScreen::updateProgress(int num) {
    bar->setValue(num);
}

void SplashScreen::showProgressMessage(int total, const QString& msg) {
    bar->setRange(0, total);
    showMessage(msg);
}
