#ifndef _MAIN_WINDOW_H 
#define _MAIN_WINDOW_H

#include <QMainWindow>
#include "flowlayout.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onAddWidget();

private:
	Ui::MainWindow* ui;
	QWidget* container;
	FlowLayout* mainLayout;
};


#endif // _MAIN_WINDOW_H