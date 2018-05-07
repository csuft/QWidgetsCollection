#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    QFile f(":/style/default.qss");
    if (f.open(QFile::ReadOnly))
    {
        const QByteArray ba = f.readAll();
        f.close();
        a.setStyleSheet(QString(ba));
    }

    MainWindow w;
    w.show();

    return a.exec();
}
