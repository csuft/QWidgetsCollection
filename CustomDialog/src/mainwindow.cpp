#include "mainwindow.h" 
#include "custompushbutton.h"
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{  
	setObjectName("main");
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
	ui.setupUi(this);   
	ui.closeBtn->setBtnBackground(":/images/close");
	ui.minimizeBtn->setBtnBackground(":/images/min");
	ui.maximizeBtn->setBtnBackground(":/images/max");

	mLocation = geometry();
	mIsMax = false;
	mMousePressed = false; 

	connect(ui.closeBtn, &QAbstractButton::clicked, this, &MainWindow::onCloseClicked); 
	connect(ui.minimizeBtn, &QAbstractButton::clicked, this, &MainWindow::onMinimizeClicked);
} 

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	if (mMousePressed && (e->buttons() && Qt::LeftButton) && !mIsMax) {
		this->move(e->globalPos() - mMousePoint);
		e->accept();
	}
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mMousePressed = true;
		mMousePoint = e->globalPos() - this->pos();
		e->accept();
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
	mMousePressed = false;
}

void MainWindow::onCloseClicked(bool checked) {
	qApp->exit();
} 

void MainWindow::onMinimizeClicked(bool checked) {
	showMinimized();
}
