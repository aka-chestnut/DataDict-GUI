#ifndef  SPLASHSCREEN_H 
#define  SPLASHSCREEN_H  
#include   < QSplashScreen > 
#include   < QProgressBar >  

namespace   Ui {
    class   SplashScreen;
}

class  SplashScreen : public   QSplashScreen {
    Q_OBJECT
public:
    explicit   SplashScreen(QPixmap  pixmap, QWidget* parent = 0);
    ~SplashScreen();
    //���ý�������      
    void  setRange(int  min, int  max);
public  slots:
    //���½���      
    void  updateProgress(int  num);
    void  showProgressMessage(int  total, const   QString& msg);
private:
    Ui::SplashScreen* ui;
    QProgressBar* bar;  //������ 
};
#endif   // SPLASHSCREEN_H
