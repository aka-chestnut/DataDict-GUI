#include "AutoHideWidget.h"
#include "QThreadc.h"
#include "QThreadt.h"
#include "QThreadDetail.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>
#include <QtCore/QVariant>
#include <QtWidgets>
#include "ShowTable.h"
#include <qdebug.h>

using namespace std;
AutoHideWidget::AutoHideWidget(QWidget* parent)
    : QWidget(parent)
    , m_mouseMovePoint(0, 0)
    , m_bMousePressed(false)
    , m_enDriection(None)
    , m_bIsAutoHide(false)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(250, 500);

    m_nDesktopWidth = QApplication::desktop()->width();
    db.createConnection("main");
    init();
}

AutoHideWidget::~AutoHideWidget()
{
    closeall();
}

void AutoHideWidget::init()
{
    this->setWindowFlags(this->windowFlags());
   

    m_pTitleWidget = new QWidget(this);
    m_pTitleWidget->setFixedHeight(360);
    m_pTitleWidget->setFixedWidth(800);
    m_pTitleWidget->installEventFilter(this);

    
    gridLayout = new QGridLayout(m_pTitleWidget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    tabWidget = new QTabWidget(m_pTitleWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setTabPosition(QTabWidget::South);
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    lineEdit_2 = new QLineEdit(tab);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setGeometry(QRect(185, 28, 470, 35));
    lineEdit_2->setMinimumSize(QSize(470, 35));
    lineEdit_2->setMaximumSize(QSize(470, 35));
    pushButton_2 = new QPushButton(tab);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(682, 29, 75, 35));
    pushButton_2->setMinimumSize(QSize(75, 35));
    pushButton_2->setMaximumSize(QSize(75, 35));
    tableWidget_2 = new QTableWidget(tab);
    tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
    tableWidget_2->setGeometry(QRect(32, 78, 735, 220));
    tableWidget_2->setMinimumSize(QSize(735, 220));
    tableWidget_2->setMaximumSize(QSize(735, 220));
    comboBox = new QComboBox(tab);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(44, 28, 120, 35));
    comboBox->setMinimumSize(QSize(120, 35));
    comboBox->setMaximumSize(QSize(120, 35));
    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tableWidget_3 = new QTableWidget(tab_2);
    tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
    tableWidget_3->setGeometry(QRect(32, 78, 735, 220));
    tableWidget_3->setMinimumSize(QSize(735, 220));
    tableWidget_3->setMaximumSize(QSize(735, 220));
    pushButton_3 = new QPushButton(tab_2);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(682, 29, 75, 35));
    pushButton_3->setMinimumSize(QSize(75, 35));
    pushButton_3->setMaximumSize(QSize(75, 35));
    lineEdit_3 = new QLineEdit(tab_2);
    lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
    lineEdit_3->setGeometry(QRect(185, 28, 470, 35));
    lineEdit_3->setMinimumSize(QSize(470, 35));
    lineEdit_3->setMaximumSize(QSize(470, 35));
    comboBox_2 = new QComboBox(tab_2);
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
    comboBox_2->setGeometry(QRect(44, 28, 120, 35));
    comboBox_2->setMinimumSize(QSize(120, 35));
    comboBox_2->setMaximumSize(QSize(120, 35));
    tabWidget->addTab(tab_2, QString());

    gridLayout->addWidget(tabWidget, 0, 0, 1, 1);
    


    tabWidget->setCurrentIndex(1);


    QMetaObject::connectSlotsByName(this);

    pCloseButton = new QPushButton(this);
    pCloseButton->setGeometry(770,5,25, 25);
    pCloseButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    pCloseButton->setFlat(true);
    pCloseButton->setStyleSheet("QPushButton"
        "{"
        "border: none;"
        "}"
        "QPushButton:hover"
        "{"
        "background: #30B7EA;"
        "}");

    connect(pCloseButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(pCloseButton, SIGNAL(clicked()), this, SLOT(closeall()));




    this->setFixedHeight(360);
    this->setFixedWidth(800);
    this->setWindowTitle(QCoreApplication::translate("QTDataDictClass", "\346\225\260\346\215\256\345\255\227\345\205\270", nullptr));
    pushButton_2->setText(QCoreApplication::translate("QTDataDictClass", "\347\241\256\345\256\232", nullptr));
    
    comboBox_2->addItems(db.v_tableSource);
    comboBox_2->setCurrentText(QString("ALL"));// 2是表
    
    tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QTDataDictClass", "\345\255\227\346\256\265\346\237\245\350\257\242", nullptr));
    pushButton_3->setText(QCoreApplication::translate("QTDataDictClass", "\347\241\256\345\256\232", nullptr));
    comboBox->addItems(db.v_colSource);
    comboBox->setCurrentText(QString("ALL")); // 1是字段
    QStringList headerscol;
    headerscol << QStringLiteral("数据库") << QStringLiteral("表名") << QStringLiteral("字段名") << QStringLiteral("描述");
    tableWidget_2->setColumnCount(4);
    tableWidget_2->setHorizontalHeaderLabels(headerscol);
    tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headerstable;
    headerstable << QStringLiteral("数据库") << QStringLiteral("表名")  << QStringLiteral("描述");
    tableWidget_3->setColumnCount(3);
    tableWidget_3->setHorizontalHeaderLabels(headerstable);
    tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QTDataDictClass", "\350\241\250\346\237\245\350\257\242", nullptr));
    tableWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(pushButton_3, SIGNAL(clicked()), this, SLOT(querytable()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(querycol()));
    connect(lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(setline3()));
    connect(lineEdit_3, SIGNAL(textChanged(QString)), this, SLOT(setline2()));
    tableWidget_2->setMouseTracking(true);
    tableWidget_3->setMouseTracking(true);
    connect(lineEdit_2, SIGNAL(returnPressed()), this, SLOT(querycol()));
    connect(lineEdit_3, SIGNAL(returnPressed()), this, SLOT(querytable()));
    connect(tableWidget_2, SIGNAL(cellEntered(int, int)), this, SLOT(slotCellEnter2(int, int)));
    connect(tableWidget_3, SIGNAL(cellEntered(int, int)), this, SLOT(slotCellEnter3(int, int)));

    connect(tableWidget_2, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(colshowtable(int, int)));
    connect(tableWidget_3, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tableshowtable(int, int)));


}



void AutoHideWidget::isAutoHide()
{
    QPoint pos = this->pos();

    m_bIsAutoHide = true;
    if (pos.x() < 2)
    {
        tabWidget->setTabPosition(QTabWidget::West);
        pCloseButton->setGeometry(5, 330, 25, 25);
        m_enDriection = Left;
    }
    else if (pos.y() < 2)
    {
        tabWidget->setTabPosition(QTabWidget::North);
        pCloseButton->setGeometry(770, 5, 25, 25);

        m_enDriection = Up;
    }
    else if (this->pos().x() + this->width() > m_nDesktopWidth - 2)
    {
        tabWidget->setTabPosition(QTabWidget::East);
        pCloseButton->setGeometry(770, 330, 25, 25);

        m_enDriection = Right;
    }
    else
    {
        tabWidget->setTabPosition(QTabWidget::South);
        pCloseButton->setGeometry(5, 5, 25, 25);

        m_enDriection = None;
        m_bIsAutoHide = false;
    }
}

void AutoHideWidget::hideWidget()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->pos(), this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), -this->height() + 2, this->size().width(), this->rect().height());




    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(-this->width() + 2, this->y(), this->size().width(), this->rect().height());

        
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - 2, this->y(), this->size().width(), this->rect().height());


    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void AutoHideWidget::showWidget()
{
    QPoint pos = this->pos();

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(pos, this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), 0, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(0, this->y(), this->size().width(), this->rect().height());

    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - this->width(), this->y(), this->size().width(), this->rect().height());

    }
    animation->setEndValue(rcEnd);
    animation->start();
}

bool AutoHideWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (m_pTitleWidget == watched)
    {
        QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (pMouseEvent != NULL)
        {

            if (pMouseEvent->type() == QEvent::MouseButtonPress)
            {
                if (pMouseEvent->button() == Qt::LeftButton)
                {
                    m_bMousePressed = true;
                    m_mouseMovePoint = pMouseEvent->pos();
                }
            }
            else if (m_bMousePressed && pMouseEvent->type() == QEvent::MouseMove)
            {
                if (!this->isMaximized())
                {
                    QPoint movePoint = pMouseEvent->globalPos();
                    this->move(movePoint - m_mouseMovePoint);
                }
            }
            else if (pMouseEvent->type() == QEvent::MouseButtonRelease)
            {
                m_bMousePressed = false;
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

bool AutoHideWidget::event(QEvent* event)
{
    if (m_bMousePressed && event->type() == QEvent::Move)
    {
        QMoveEvent* pMoveEvent = dynamic_cast<QMoveEvent*>(event);

        if (pMoveEvent != NULL)
        {
            QPoint pos = pMoveEvent->pos();
            if (pos.x() < 0)
            {
                pos.setX(0);
            }
            if (pos.y() < 0)
            {
                pos.setY(0);
            }
            if (pos.x() + this->width() > m_nDesktopWidth)
            {
                pos.setX(m_nDesktopWidth - this->width());
            }
            else {
                ;
            }

            event->ignore();
            this->move(pos);
        }
    }
    return QWidget::event(event);
}

void AutoHideWidget::leaveEvent(QEvent* event)
{
    isAutoHide();
    if (m_bIsAutoHide)
    {
        hideWidget();
    }
}

void AutoHideWidget::enterEvent(QEvent* event)
{
    if (m_bIsAutoHide)
    {
        showWidget();
    }
}

void AutoHideWidget::querytable()
{
    if (comboBox_2->currentText() == "ALL")
    {
        QString sql = "select db_name,table_name,table_desc from table_info where table_name like '%" + lineEdit_3->text().replace(" ", "") + "%' or table_desc like '%" + lineEdit_3->text().replace(" ", "") + "%' order by table_name";
        QThreadt* dbt = new QThreadt(sql,"dt");
        connect(dbt, SIGNAL(sendtable(QStringList)), this, SLOT(UpdateTableView(QStringList)));
        connect(dbt, SIGNAL(finished()), dbt, SLOT(deleteLater()));
        dbt->start();
    }
    else
    {
        QString sql = "select db_name,table_name,table_desc from table_info where (table_name like '%" + lineEdit_3->text().replace(" ", "") + "%' or table_desc like '%" + lineEdit_3->text().replace(" ", "") + "%') and db_name='" + comboBox_2->currentText()+"' order by table_name";
        QThreadt* dbt = new QThreadt(sql,"dt");
        connect(dbt, SIGNAL(sendtable(QStringList)), this, SLOT(UpdateTableView(QStringList)));
        connect(dbt, SIGNAL(finished()), dbt, SLOT(deleteLater()));
        dbt->start();
    }
}

void AutoHideWidget::querycol()
{
    if (comboBox->currentText() == "ALL")
    {
        QString sql = "select * from col_info where column_name like '%" + lineEdit_2->text().replace(" ","") + "%' or column_desc like '%" + lineEdit_2->text().replace(" ", "") + "%' order by column_name";
        QThreadc* dbc = new QThreadc(sql,"dc");
        connect(dbc, SIGNAL(sendcol(QStringList)), this, SLOT(UpdateColView(QStringList)));
        connect(dbc, SIGNAL(finished()), dbc, SLOT(deleteLater()));
        dbc->start();
    }
    else
    {
        QString sql = "select * from col_info where (column_name like '%" + lineEdit_2->text().replace(" ", "") + "%' or column_desc like '%" + lineEdit_2->text().replace(" ", "") + "%') and upper(hive_db)='" + comboBox->currentText()+"' order by column_name";
        QThreadc* dbc = new QThreadc(sql,"dc");
        connect(dbc, SIGNAL(sendcol(QStringList)), this, SLOT(UpdateColView(QStringList)));
        connect(dbc, SIGNAL(finished()), dbc, SLOT(deleteLater()));
        dbc->start();
    }
}

void AutoHideWidget::UpdateTableView(QStringList a)
{
    tableWidget_3->clearContents();
    tableWidget_3->setRowCount(0);
    for (int i = 0; i < a.size(); ++i)
    {
        QString tmp = a.at(i);
        QStringList tmplist = tmp.split('\t');
        int RowCont;
        RowCont = tableWidget_3->rowCount();
        tableWidget_3->insertRow(RowCont);//增加一行

        //插入元素
        tableWidget_3->setItem(RowCont, 0, new QTableWidgetItem(tmplist.at(0)));
        tableWidget_3->setItem(RowCont, 1, new QTableWidgetItem(tmplist.at(1)));
        tableWidget_3->setItem(RowCont, 2, new QTableWidgetItem(tmplist.at(2)));

    }
    tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void AutoHideWidget::UpdateColView(QStringList a)
{
    tableWidget_2->clearContents();
    tableWidget_2->setRowCount(0);
    for (int i = 0; i < a.size(); ++i)
    {
        QString tmp = a.at(i);
        QStringList tmplist = tmp.split('\t');
        int RowCont;
        RowCont = tableWidget_2->rowCount();
        tableWidget_2->insertRow(RowCont);//增加一行

        //插入元素
        tableWidget_2->setItem(RowCont, 0, new QTableWidgetItem(tmplist.at(0)));
        tableWidget_2->setItem(RowCont, 1, new QTableWidgetItem(tmplist.at(1)));
        tableWidget_2->setItem(RowCont, 2, new QTableWidgetItem(tmplist.at(2)));
        tableWidget_2->setItem(RowCont, 3, new QTableWidgetItem(tmplist.at(3)));

    }
    tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  
    tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void AutoHideWidget::setline3()
{
    lineEdit_3->setText(lineEdit_2->text());
}

void AutoHideWidget::setline2()
{
    lineEdit_2->setText(lineEdit_3->text());
}

void AutoHideWidget::slotCellEnter2(int row, int col)
{
    QTableWidgetItem* item = tableWidget_2->item(row, col);
    if (item == NULL) {
        return;
    }
    QToolTip::showText(QCursor::pos(), item->text());
}

void AutoHideWidget::slotCellEnter3(int row, int col)
{
    QTableWidgetItem* item = tableWidget_3->item(row, col);
    if (item == NULL) {
        return;
    }
    QToolTip::showText(QCursor::pos(), item->text());
}

void AutoHideWidget::colshowtable(int row, int col)
{
    ShowTable* tableDetail = new ShowTable();

    if (col == 1) {
        tableDetail->showNormal();
        tableDetail->setWindowTitle(tableWidget_2->item(row, col)->text());
        tableDetail->show();
        v_showtable.push_back(tableDetail);

        QString sql = "select * from col_info where hive_table='" + tableWidget_2->item(row, col)->text()+"' order by column_name";
        QThreadDetail* dbdt = new QThreadDetail(sql, "dbdt");
        connect(dbdt, SIGNAL(senddetails(QStringList)), v_showtable.back(), SLOT(UpdateDetailView(QStringList)));
        connect(dbdt, SIGNAL(finished()), dbdt, SLOT(deleteLater()));
        dbdt->start();

    }

}
void AutoHideWidget::tableshowtable(int row, int col)
{
    ShowTable* tableDetail = new ShowTable();

    if (col == 1) {
        tableDetail->showNormal();
        tableDetail->setWindowTitle(tableWidget_3->item(row, col)->text()+" " + tableWidget_3->item(row, col+1)->text() );
        tableDetail->show();
        v_showtable.push_back(tableDetail);
        QString sql = "select * from col_info where hive_table='"+ tableWidget_3->item(row, col)->text()+"' order by column_name";
        QThreadDetail* dbdt = new QThreadDetail(sql, "dbdt");
        connect(dbdt, SIGNAL(senddetails(QStringList)),v_showtable.back() , SLOT(UpdateDetailView(QStringList)));
        connect(dbdt, SIGNAL(finished()), dbdt, SLOT(deleteLater()));
        dbdt->start();

    }
}

void AutoHideWidget::closeall()
{
    vector<ShowTable*>::iterator it = v_showtable.begin();
    for (; it != v_showtable.end(); ++it)
    {
        ShowTable* tmp = *it;
        tmp->close();
        *it = NULL;
        delete tmp;
    }
    v_showtable.clear();
}

