#include "mainwindow.h"
#include <QFile>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile file(":/style/app");
	bool ret = file.open(QFile::ReadOnly);
	if (ret) {
		qApp->setStyleSheet(file.readAll());
		file.close();
	}

	MainWindow w; 
	w.show();
	return a.exec();
}
