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

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		origin = event->pos();
		rubberBand = std::make_shared<CustomRubberBand>(QRubberBand::Rectangle, this);
		rubberBand->setGeometry(QRect(origin, QSize()));
		rubberBand->show();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	if (rubberBand) {
		rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {

}


MainWindow::~MainWindow() {

}