#include "footageListDock.h"
#include <QHBoxLayout>

#include "titlebar.h"

namespace studio {

	FootageListDock::FootageListDock(QWidget* parent)
		: QDockWidget(parent) { 
		setObjectName("footagelistDock");
		setWindowTitle(tr("Footage List")); 
		setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		
        QHBoxLayout* mainLayout = new QHBoxLayout;
		mFootageList = new FootageListWidget(this);
        mFootageList->setRowCount(3);
        mFootageList->setColumnCount(1);
        mFootageList->setItem(0,0,new QTableWidgetItem("Jan"));
        mFootageList->setItem(1,0,new QTableWidgetItem("Feb"));
        mFootageList->setItem(2,0,new QTableWidgetItem("Mar"));
        mFootageList->setRowCount(mFootageList->rowCount() + 1);
        mFootageList->setItem(3,0, new QTableWidgetItem("April"));

		mainLayout->addWidget(mFootageList);
		QWidget* centralWidget = new QWidget(this);
		centralWidget->setLayout(mainLayout);
		setWidget(centralWidget);
		TitleBar* titleBar = new TitleBar("Footage List", this);
		setTitleBarWidget(titleBar);
	} 

	void FootageListDock::addFootage(const QList<QUrl>& files) {
		mFootageList->addFootage(files);
	}

	bool FootageListDock::removeFootage(const QList<QUrl>& files) {
		return mFootageList->removeFootage(files); 
	}
}
