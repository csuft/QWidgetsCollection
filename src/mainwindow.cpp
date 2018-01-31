#include "mainwindow.h"
#include "customitemdelegate.h"
#include "customitemmodel.h"
#include "customtableview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTextEdit>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);  
	CustomTableView* tableView = new CustomTableView(this);
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(tableView);

	TableViewDelegate* tableViewDelegate = new TableViewDelegate(tableView);
	
	setStyleSheet("background: rgb(36,37,38);"); 
	CustomItemModel* itemModel = new CustomItemModel(QVector<int>{0, 1}, this);
	itemModel->setColumnCount(3);
	tableView->setModel(itemModel);
	tableView->horizontalHeader()->setHidden(true);
	tableView->horizontalHeader()->setStretchLastSection(true);
	tableView->verticalHeader()->setHidden(true);
	tableView->setSortingEnabled(true);
	tableView->setWordWrap(false);
	tableView->setMouseTracking(true);
	tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->setShowGrid(false);
	tableView->setItemDelegate(tableViewDelegate);
	tableView->setFrameShape(QFrame::NoFrame);
	tableView->setAlternatingRowColors(false);
	tableView->setColumnWidth(0, 20);
	tableView->setColumnWidth(1, 160);
	tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	for (int i = 0; i < 10; i++) {
		itemModel->insertRow(i);
		itemModel->setData(itemModel->index(i, 0), QString::number(i));
		itemModel->setData(itemModel->index(i, 0), QString::number(i), Qt::ToolTipRole);
		itemModel->setData(itemModel->index(i, 1), "zhangzhongke");
		itemModel->setData(itemModel->index(i, 1), "HUST", Qt::ToolTipRole);
	}
	connect(tableView, &CustomTableView::hoverIndexChanged, tableViewDelegate, &TableViewDelegate::onHoverIndexChanged);
	setLayout(mainLayout);
}
