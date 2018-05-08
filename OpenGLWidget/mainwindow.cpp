#include "mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent) {
	resize(760, 490);
	QVBoxLayout* mainLayout = new QVBoxLayout;

	displayWidget = new GLWidget(this);
	displayWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	updateBtn = new QPushButton("update texture", this);
	mainLayout->addWidget(displayWidget);
	mainLayout->addWidget(updateBtn, 0, Qt::AlignRight | Qt::AlignBottom);
	
	container = new QWidget(this);
	container->setLayout(mainLayout);
	setCentralWidget(container);
	connect(updateBtn, &QAbstractButton::clicked, this, &MainWindow::onUpdateTexture);
}

void MainWindow::onUpdateTexture() {
	QString filePath = QFileDialog::getOpenFileName(this, "open texture image", 
		QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)[0],
		tr("Image Files(*.png *.jpg *.bmp)"));
	if (!filePath.isEmpty()) {
		QImage imageFile(filePath);
		QImage convertedImage = imageFile.convertToFormat(QImage::Format_RGB888).rgbSwapped();
		if (!convertedImage.isNull()) {
			displayWidget->setFrameData(QOpenGLTexture::BGR, QOpenGLTexture::UInt8,
				convertedImage.bits(), convertedImage.width(), convertedImage.height());
		}
	}
}

MainWindow::~MainWindow() {

}