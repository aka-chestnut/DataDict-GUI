#ifndef AUTOHIDEWIDGET_H
#define AUTOHIDEWIDGET_H
#include <vector>
#include <string>
#include "DataBase.h"
#include "ShowTable.h"
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
using namespace std;

class AutoHideWidget : public QWidget
{
    Q_OBJECT
public:

    enum Direction
    {
        None,
        Up,
        Right,
        Down,
        Left
    };

public:
    AutoHideWidget(QWidget* parent = 0);
    ~AutoHideWidget();

private:

    void init();
    void isAutoHide();
    void hideWidget();
    void showWidget();

private:
    DataBase db;
    QPushButton* pCloseButton;
    QWidget* m_pTitleWidget;
    QWidget* m_pContentWidget;
    QPoint m_mouseMovePoint;
    bool m_bMousePressed;
    Direction m_enDriection;
    bool m_bIsAutoHide;
    int m_nDesktopWidth;
    QWidget* centralWidget;
    QGridLayout* gridLayout;
    QTabWidget* tabWidget;
    QWidget* tab;
    QLineEdit* lineEdit_2;
    QPushButton* pushButton_2;
    QTableWidget* tableWidget_2;
    QComboBox* comboBox;
    QWidget* tab_2;
    QTableWidget* tableWidget_3;
    QPushButton* pushButton_3;
    QLineEdit* lineEdit_3;
    QComboBox* comboBox_2;
    QToolBar* mainToolBar;
    vector<ShowTable*> v_showtable;
    


public:
    bool eventFilter(QObject* watched, QEvent* event);
    bool event(QEvent* event);
    void leaveEvent(QEvent* event);
    void enterEvent(QEvent* event);
  
private slots:
    void querytable();
    void querycol();
    void UpdateTableView(QStringList a);
    void UpdateColView(QStringList a);
    void setline3(void);
    void setline2();
    void slotCellEnter2(int row, int col);
    void slotCellEnter3(int row, int col);
    void colshowtable(int row, int col);
    void tableshowtable(int row, int col);
    void closeall();

};

#endif // AUTOHIDEWIDGET_H
