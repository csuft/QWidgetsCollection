#ifndef _MAIN_WINDOW_H 
#define _MAIN_WINDOW_H

#include <QMainWindow>
#include "glwidget.h" 

class QPushButton;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onUpdateTexture();

private: 
	QWidget* container;
	GLWidget* displayWidget;
	QPushButton* updateBtn;
};


#endif // _MAIN_WINDOW_H