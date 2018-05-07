#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "footageListDock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void onAddDockWidget();

private:
    Ui::MainWindow *ui;
    studio::FootageListDock* mFootageListDock1;
	studio::FootageListDock* mFootageListDock2;
};

#endif // MAINWINDOW_H
