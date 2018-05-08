#ifndef _MAIN_WINDOW_H 
#define _MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include "overlay.h" 

class QPushButton;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow(); 

protected:
	virtual void mousePressEvent(QMouseEvent *e) override;

private:
	std::shared_ptr<Overlay> overlay;
};


#endif // _MAIN_WINDOW_H