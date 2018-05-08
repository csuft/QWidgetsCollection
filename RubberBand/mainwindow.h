#ifndef _MAIN_WINDOW_H 
#define _MAIN_WINDOW_H

#include <QMainWindow>
#include <memory>
#include "customrubberband.h" 

class QPushButton;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	virtual void mousePressEvent(QMouseEvent *e) override; 
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QPoint origin;
	std::shared_ptr<CustomRubberBand> rubberBand;
};


#endif // _MAIN_WINDOW_H