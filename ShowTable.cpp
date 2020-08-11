#include "ShowTable.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>
#include <QtCore/QVariant>
#include <QtWidgets>
using namespace std;
ShowTable::ShowTable(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
    init();
}

void ShowTable::createMenuBar()
{
    QMenuBar* mMenu = new QMenuBar(this);
    mMenu->setGeometry(0, 0, this->width(), 200);
    QMenu* menuFile;
    QMenu* menuTool;
    QMenu* menuAllSQL;
    QMenu* menuPartSQL;
    menuFile = new QMenu(QStringLiteral("文件"),this);
    menuTool = new QMenu(QStringLiteral("工具"), this);
    menuAllSQL = new QMenu(QStringLiteral("复制完整SQL"), this);
    menuPartSQL = new QMenu(QStringLiteral("复制部分SQL"),this);
    mMenu->addMenu(menuFile);
    QAction *actionCopyall = new QAction(QStringLiteral("全部复制"), this);
    menuFile->addAction(actionCopyall);
    mMenu->addMenu(menuTool);
    menuTool->addMenu(menuAllSQL);
    menuTool->addMenu(menuPartSQL);
    QAction* actionCopyAllSQL = new QAction(QStringLiteral("SQL语句"), this);
    QAction* actionCopyAllSQLWithW = new QAction(QStringLiteral("SQL语句带注释"), this);
    QAction* actionCopyAllSQLWithA = new QAction(QStringLiteral("SQL语句带别名"), this);
    QAction* actionCopyAllSQLWithWA = new QAction(QStringLiteral("SQL语句带注释和别名"), this);
    menuAllSQL->addAction(actionCopyAllSQL);
    menuAllSQL->addAction(actionCopyAllSQLWithW);
    menuAllSQL->addAction(actionCopyAllSQLWithA);
    menuAllSQL->addAction(actionCopyAllSQLWithWA);

    QAction* actionCopyPartSQL = new QAction(QStringLiteral("SQL语句Part"), this);
    QAction* actionCopyPartSQLWithW = new QAction(QStringLiteral("SQL语句带注释Part"), this);
    QAction* actionCopyPartSQLWithA = new QAction(QStringLiteral("SQL语句带别名Part"), this);
    QAction* actionCopyPartSQLWithWA = new QAction(QStringLiteral("SQL语句带注释和别名Part"), this);
    menuPartSQL->addAction(actionCopyPartSQL);
    menuPartSQL->addAction(actionCopyPartSQLWithW);
    menuPartSQL->addAction(actionCopyPartSQLWithA);
    menuPartSQL->addAction(actionCopyPartSQLWithWA);



    QAction* actionCopyName = new QAction(QStringLiteral("复制库名+表名"), this);
    menuTool->addAction(actionCopyName);
    QAction* actionSearch = new QAction(QStringLiteral("搜索"), this);
    menuTool->addAction(actionSearch);
    actionCopyall->setShortcut(QStringLiteral("Ctrl+Alt+C"));
    actionCopyName->setShortcut(QStringLiteral("Ctrl+Alt+1"));
    actionCopyAllSQLWithW->setShortcut(QStringLiteral("Ctrl+Alt+2"));
    actionCopyPartSQLWithW->setShortcut(QStringLiteral("Ctrl+Alt+3"));

    actionSearch->setShortcut(QStringLiteral("Ctrl+F"));
    connect(actionCopyall, SIGNAL(triggered(bool)), this, SLOT(copyAll()));
    connect(actionCopyName, SIGNAL(triggered(bool)), this, SLOT(copyName()));

    connect(actionCopyAllSQL, SIGNAL(triggered(bool)), this, SLOT(copyallsql()));
    connect(actionCopyAllSQLWithW, SIGNAL(triggered(bool)), this, SLOT(copyallsqlwithw()));
    connect(actionCopyAllSQLWithA, SIGNAL(triggered(bool)), this, SLOT(copyallsqlwitha()));
    connect(actionCopyAllSQLWithWA, SIGNAL(triggered(bool)), this, SLOT(copyallsqlwithwa()));

    connect(actionCopyPartSQL, SIGNAL(triggered(bool)), this, SLOT(copypartsql()));
    connect(actionCopyPartSQLWithW, SIGNAL(triggered(bool)), this, SLOT(copypartsqlwithw()));
    connect(actionCopyPartSQLWithA, SIGNAL(triggered(bool)), this, SLOT(copypartsqlwitha()));
    connect(actionCopyPartSQLWithWA, SIGNAL(triggered(bool)), this, SLOT(copypartsqlwithwa()));

    connect(actionSearch, SIGNAL(triggered(bool)), this, SLOT(onSearch()));


}
void ShowTable::init()
{
    createMenuBar();
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 30, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    tableWidget = new QTableWidget(this);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // todo: 改成vector的tablewidget和vector的myheader
    horizontalLayout->addWidget(tableWidget);

    //动作初始化

    QStringList headerscoldetails;
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    headerscoldetails << QStringLiteral("数据库") << QStringLiteral("表名") << QStringLiteral("选择") << QStringLiteral("字段名") << QStringLiteral("描述");
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(headerscoldetails);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
}

ShowTable::~ShowTable()
{
}

void ShowTable::UpdateDetailView(QStringList a)
{

    for (int i = 0; i < a.size(); ++i)
    {
        QCheckBox* p_check = new QCheckBox();

        p_check->setCheckState(Qt::Unchecked);
        QString tmp = a.at(i);
        QStringList tmplist = tmp.split('\t');
        int RowCont;
        RowCont = tableWidget->rowCount();
        tableWidget->insertRow(RowCont);//增加一行

        QWidget* w = new QWidget(this); //创建一个widget
        QHBoxLayout* hLayout = new QHBoxLayout(); //创建布局
        hLayout->addWidget(p_check); //添加checkbox
        hLayout->setMargin(0); //设置边缘距离 否则会很难看
        hLayout->setAlignment(p_check, Qt::AlignCenter); //居中
        w->setLayout(hLayout); //设置widget的布局
        //插入元素
        tableWidget->setItem(RowCont, 0, new QTableWidgetItem(tmplist.at(0)));
        tableWidget->setItem(RowCont, 1, new QTableWidgetItem(tmplist.at(1)));
        tableWidget->setItem(RowCont, 3, new QTableWidgetItem(tmplist.at(2)));
        tableWidget->setItem(RowCont, 4, new QTableWidgetItem(tmplist.at(3)));
        tableWidget->setCellWidget(RowCont, 2, w);
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    connect(tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(setCopyContext(QPoint)));

}

// 右键菜单（弹出窗口）
void ShowTable::setCopyContext(QPoint pos)
{

    popMenu = new QMenu(tableWidget);
    cpaction = new QAction(QStringLiteral("复制"), this);
    cpsqlaction = new QAction(QStringLiteral("复制SQL"), this);
    cpsqlwaction = new QAction(QStringLiteral("复制带注释SQL"), this);
    cpsqlasaction = new QAction(QStringLiteral("复制带别名SQL"), this);
    cpsqlaswaction = new QAction(QStringLiteral("复制带别名注释SQL"), this);

    cppartsqlaction = new QAction(QStringLiteral("复制SQL"), this);
    cppartsqlwaction = new QAction(QStringLiteral("复制带注释SQL"), this);
    cppartsqlasaction = new QAction(QStringLiteral("复制带别名SQL"), this);
    cppartsqlaswaction = new QAction(QStringLiteral("复制带别名注释SQL"), this);
    popMenu->addAction(cpaction); // 复制
    QMenu* cpSQL = popMenu->addMenu(QStringLiteral("复制完整SQL")); // 完整SQL二级菜单
    cpSQL->addAction(cpsqlaction);
    cpSQL->addAction(cpsqlwaction);
    cpSQL->addAction(cpsqlasaction);
    cpSQL->addAction(cpsqlaswaction);
    QMenu* cpPartSQL = popMenu->addMenu(QStringLiteral("复制部分SQL"));
    cpPartSQL->addAction(cppartsqlaction);
    cpPartSQL->addAction(cppartsqlwaction);
    cpPartSQL->addAction(cppartsqlasaction);
    cpPartSQL->addAction(cppartsqlaswaction);

    connect(cpaction, SIGNAL(triggered(bool)), this, SLOT(context2clip()));
    connect(cpsqlaction, SIGNAL(triggered(bool)), this, SLOT(context2sql()));
    connect(cpsqlwaction, SIGNAL(triggered(bool)), this, SLOT(context2sqlwithwords()));
    connect(cpsqlasaction, SIGNAL(triggered(bool)), this, SLOT(context2sqlwithas()));
    connect(cpsqlaswaction, SIGNAL(triggered(bool)), this, SLOT(context2sqlwithaswords()));

    connect(cppartsqlaction, SIGNAL(triggered(bool)), this, SLOT(partcontext2sql()));
    connect(cppartsqlwaction, SIGNAL(triggered(bool)), this, SLOT(partcontext2sqlwithwords()));
    connect(cppartsqlasaction, SIGNAL(triggered(bool)), this, SLOT(partcontext2sqlwithas()));
    connect(cppartsqlaswaction, SIGNAL(triggered(bool)), this, SLOT(partcontext2sqlwithaswords()));


    popMenu->exec(QCursor::pos());

}
void ShowTable::context2clip()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;

    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }


    QString clipText;
    for (int i = topRow; i <= buttomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            clipText.append("\t");
        }
        clipText.chop(1);
        clipText.append("\n");
    }

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}



// 完整sql复制
void ShowTable::context2sql()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 3 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }


    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = topRow; i <= buttomRow; i++) {

        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            if (i != buttomRow)
                clipText.append(",");
        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::context2sqlwithwords()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 4 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }

    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = topRow; i <= buttomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            if (j == 3)
                if (i != buttomRow)
                    clipText.append(",        -- ");
                else
                    clipText.append("        -- ");

        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::context2sqlwithas()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 3 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);

    if (!bOk)
        return;
    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = topRow; i <= buttomRow; i++) {

        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            clipText.append(" AS ");
            clipText.append(tmpas + "_" + text);
            if (i != buttomRow)
                clipText.append(",");
        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::context2sqlwithaswords()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 4 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);

    if (!bOk)
        return;
    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = topRow; i <= buttomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);


            if (j == 3)
                if (i != buttomRow)
                    clipText.append(" AS " + tmpas + "_" + text + "," + "        -- ");
                else
                    clipText.append(" AS " + tmpas + "_" + text + "        -- ");


        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

// 追加sql复制
void ShowTable::partcontext2sql()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 3 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }


    QString clipText;

    for (int i = topRow; i <= buttomRow; i++) {

        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            clipText.append(",");
        }
        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::partcontext2sqlwithwords()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 4 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }

    QString clipText;

    for (int i = topRow; i <= buttomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            if (j == 3)
                clipText.append(",        -- ");


        }
        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::partcontext2sqlwithas()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 3 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);

    if (!bOk)
        return;
    QString clipText;

    for (int i = topRow; i <= buttomRow; i++) {

        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            clipText.append(" AS ");
            clipText.append(tmpas + "_" + text);
            clipText.append(",");
        }
        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::partcontext2sqlwithaswords()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if (tableWidgetItem.count() == 0)
        return;


    int topRow, buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange = tableWidget->selectedRanges();
    for (int i = 0; i < tableSelectRange.count(); i++)
    {
        topRow = tableSelectRange.at(i).topRow();
        buttomRow = tableSelectRange.at(i).bottomRow();
        leftColumn = tableSelectRange.at(i).leftColumn();
        rightColumn = tableSelectRange.at(i).rightColumn();
    }
    if (rightColumn != 4 || leftColumn != 3)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("所选内容区域不符合功能要求！"), QMessageBox::Yes);
        return;
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);

    if (!bOk)
        return;
    QString clipText;

    for (int i = topRow; i <= buttomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);


            if (j == 3)
                clipText.append(" AS " + tmpas + "_" + text + "," + "        -- ");



        }
        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

}

void ShowTable::copyAll()
{
    int RowCont = tableWidget->rowCount();
    int ColCont = tableWidget->columnCount();
    QString clipText;
    for (int i = 0; i < RowCont; i++) {
        for (int j = 0; j <= ColCont; j++) {
            if (j == 2) continue;
            QString text;
            if (tableWidget->item(i, j) != nullptr)
                text = tableWidget->item(i, j)->text();
            clipText.append(text);
            clipText.append("\t");
        }
        clipText.chop(1);
        clipText.append("\n");

    }   
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);
}

void ShowTable::copyName()
{
    QString clipText; 
    clipText = tableWidget->item(0, 0)->text() + "." + tableWidget->item(0, 1)->text();
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);


}

void ShowTable::copyallsql()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget *w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));  
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked) 
                {
                    tmp.push_back(i);
                }
            }

        }
    }

    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i =0; i<tmp.size(); i++)
    {
        QString text;
        
        text = tableWidget->item(tmp[i], 3)->text();
        clipText.append(text);
        if (i != tmp.size() - 1)
        {
            clipText.append(",");
        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

    vector<int>(tmp).swap(tmp);

}

void ShowTable::copyallsqlwithw()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked) 
                {
                    tmp.push_back(i);
                }
            }

        }
    }

    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1,text2;

        text1 = tableWidget->item(tmp[i], 3)->text();
        text2 = tableWidget->item(tmp[i], 4)->text();
        if (i != tmp.size() - 1)
        {
            clipText.append(text1+",    -- "+text2);
        }
        else
        {
            clipText.append(text1 + "    -- " + text2);
        }
        clipText.append("\n");
    }
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

    vector<int>(tmp).swap(tmp);

}

void ShowTable::copyallsqlwitha()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);
    if (!bOk)
        return;
    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1, text2;

        text1 = tableWidget->item(tmp[i], 3)->text();
        if (i != tmp.size() - 1)
        {
            clipText.append(text1 + " AS " + tmpas+"_"+text1+ ",");
        }
        else
        {
            clipText.append(text1 + " AS " + tmpas + "_" + text1 );
        }
        clipText.append("\n");
    }
    
    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);
    vector<int>(tmp).swap(tmp);

}

void ShowTable::copyallsqlwithwa()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);
    if (!bOk)
        return;
    QString clipText;
    clipText.append("SELECT");
    clipText.append("\n");
    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1, text2;

        text1 = tableWidget->item(tmp[i], 3)->text();
        text2 = tableWidget->item(tmp[i], 4)->text();
        if (i != tmp.size() - 1)
        {
            clipText.append(text1 + " AS " + tmpas + "_" + text1 + ",    -- "+text2);
        }
        else
        {
            clipText.append(text1 + " AS " + tmpas + "_" + text1 + "    -- "+text2);
        }
        clipText.append("\n");
    }

    clipText.append("FROM ");
    clipText.append(tableWidget->item(0, 0)->text());
    clipText.append(".");
    clipText.append(tableWidget->item(0, 1)->text());
    clipText.append(";");

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);
    vector<int>(tmp).swap(tmp);
}

void ShowTable::copypartsql()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }

    QString clipText;

    for (int i = 0; i < tmp.size(); i++)
    {
        QString text;

        text = tableWidget->item(tmp[i], 3)->text();
        clipText.append(text);
        
        clipText.append(",");
        
        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

    vector<int>(tmp).swap(tmp);
}

void ShowTable::copypartsqlwithw()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }

    QString clipText;

    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1, text2;

        text1 = tableWidget->item(tmp[i], 3)->text();
        text2 = tableWidget->item(tmp[i], 4)->text();

        clipText.append(text1 + ",    -- " + text2);

        clipText.append("\n");
    }


    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);

    vector<int>(tmp).swap(tmp);
}

void ShowTable::copypartsqlwitha()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);
    if (!bOk)
        return;
    QString clipText;

    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1, text2;

        text1 = tableWidget->item(tmp[i], 3)->text();

        clipText.append(text1 + " AS " + tmpas + "_" + text1 + ",");

        clipText.append("\n");
    }



    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);
    vector<int>(tmp).swap(tmp);
}

void ShowTable::copypartsqlwithwa()
{
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (QWidget* w = tableWidget->cellWidget(i, 2))
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(w->children().at(1));
            if (checkBox)
            {
                if (checkBox->checkState() == Qt::Checked)
                {
                    tmp.push_back(i);
                }
            }

        }
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("别名"), QStringLiteral("请输入别名英文前缀，将自动生成带前缀的变量名"), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);
    if (!bOk)
        return;
    QString clipText;

    for (int i = 0; i < tmp.size(); i++)
    {
        QString text1, text2;

        text1 = tableWidget->item(tmp[i], 3)->text();
        text2 = tableWidget->item(tmp[i], 4)->text();

        clipText.append(text1 + " AS " + tmpas + "_" + text1 + ",    -- " + text2);

        clipText.append("\n");
    }



    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipText);
    vector<int>(tmp).swap(tmp);
}

void ShowTable::onSearch()
{
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 2)
                continue;
            tableWidget->item(i, j)->setBackgroundColor(QColor(Qt::white));
        }
    }
    bool bOk = false;
    QString tmpas = QInputDialog::getText(this, QStringLiteral("搜索"), QStringLiteral("请输入所需搜索的字段名或中文注释："), QLineEdit::Normal, tableWidget->item(0, 0)->text(), &bOk);
    if (!bOk)
        return;
    vector<int> tmp;
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (tableWidget->item(i, 3)->text().contains(tmpas.replace(" ", ""), Qt::CaseInsensitive) || tableWidget->item(i, 4)->text().contains(tmpas.replace(" ", ""), Qt::CaseInsensitive))
        {
            tmp.push_back(i);
        }
    }
    for (int i = 0; i < tmp.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 2)
                continue;
            tableWidget->item(tmp[i], j)->setBackgroundColor(QColor(Qt::yellow));
        }
    }
    vector<int>(tmp).swap(tmp);

}