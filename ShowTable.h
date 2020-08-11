#pragma once

#include <QWidget>
#include "ui_ShowTable.h"
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QHBoxLayout>
class Action;
class QMenu;
class QWidget;


class ShowTable : public QWidget
{
Q_OBJECT

public:
	ShowTable(QWidget *parent = Q_NULLPTR);
	~ShowTable();


	QHBoxLayout* horizontalLayout;
	QTableWidget* tableWidget;

private:
	QMenu* popMenu;
	QAction* cpaction;
	QAction* cpsqlaction;
	QAction* cpsqlwaction;
	QAction* cpsqlasaction;
	QAction* cpsqlaswaction;
	QAction* cppartsqlaction;
	QAction* cppartsqlwaction;
	QAction* cppartsqlasaction;
	QAction* cppartsqlaswaction;
	Ui::ShowTable ui;
	void createMenuBar();
	void init();
private slots:
	void UpdateDetailView(QStringList a);
	void setCopyContext(QPoint pos);
	void context2clip();
	void context2sql();
	void context2sqlwithwords();
	void context2sqlwithas();
	void context2sqlwithaswords();
	void partcontext2sql();
	void partcontext2sqlwithwords();
	void partcontext2sqlwithas();
	void partcontext2sqlwithaswords();
	void copyAll();
	void copyName();
	void copyallsql();
	void copyallsqlwithw();
	void copyallsqlwitha();
	void copyallsqlwithwa();
	void copypartsql();
	void copypartsqlwithw();
	void copypartsqlwitha();
	void copypartsqlwithwa();
	void onSearch();

};

