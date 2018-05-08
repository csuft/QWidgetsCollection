#include "mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent) {
	resize(760, 490);
	 
} 

void MainWindow::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		QPoint mousePos = e->pos();
		overlay = std::make_shared<Overlay>("test", mousePos, this);
		overlay->show();
	} 
}

MainWindow::~MainWindow() {

}