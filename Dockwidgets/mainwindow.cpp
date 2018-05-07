#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->actionLeftArea->setData("left");
	ui->actionRightArea->setData("right");
	ui->actionTopArea->setData("top");
	ui->actionBottomArea->setData("bottom");
	setWindowIcon(QIcon(":/image/logo"));
    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
    this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

    mFootageListDock1 = new studio::FootageListDock(this);
    addDockWidget(Qt::LeftDockWidgetArea, mFootageListDock1);
	mFootageListDock2 = new studio::FootageListDock(this);
	addDockWidget(Qt::RightDockWidgetArea, mFootageListDock2);

	connect(ui->actionBottomArea, &QAction::triggered, this, &MainWindow::onAddDockWidget);
	connect(ui->actionTopArea, &QAction::triggered, this, &MainWindow::onAddDockWidget);
	connect(ui->actionLeftArea, &QAction::triggered, this, &MainWindow::onAddDockWidget);
	connect(ui->actionRightArea, &QAction::triggered, this, &MainWindow::onAddDockWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onAddDockWidget() {
	QDockWidget* dockWidget = new studio::FootageListDock(this);;
	QAction* action = qobject_cast<QAction*>(sender());
	if (!action->data().compare("left")) { 
		addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	}
	else if (!action->data().compare("right")) {
		addDockWidget(Qt::RightDockWidgetArea, dockWidget);
	}
	else if (!action->data().compare("top")) {
		addDockWidget(Qt::TopDockWidgetArea, dockWidget);
	}
	else {
		addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
	} 
}