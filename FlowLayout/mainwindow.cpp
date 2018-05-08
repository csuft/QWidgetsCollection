#include "mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	mainLayout = new FlowLayout;
	container = new QWidget(this);
	container->setLayout(mainLayout);
	setCentralWidget(container);
	connect(ui->actionAddWidget, &QAction::triggered, this, &MainWindow::onAddWidget);
}

void MainWindow::onAddWidget() {
	QPushButton* button = new QPushButton("Test Button", this);
	mainLayout->addWidget(button);
}

MainWindow::~MainWindow() {

}