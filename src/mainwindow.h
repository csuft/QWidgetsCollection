#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainwindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR); 

private:
	Ui::mainwindow ui;
};
