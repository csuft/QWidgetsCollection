#ifndef _FOOTAGE_LIST_DOCK_H
#define _FOOTAGE_LIST_DOCK_H

#include <QDockWidget>
#include "footageList.h"

namespace studio {
	class FootageListDock : public QDockWidget {
		Q_OBJECT
	public:
		explicit FootageListDock(QWidget* parent = Q_NULLPTR);
		~FootageListDock() {}

		QSize minimumSizeHint() const override {
			return QSize(256, 256);
		}

		void addFootage(const QList<QUrl>& files);
		bool removeFootage(const QList<QUrl>& files); 

	private:
		FootageListWidget* mFootageList;
	};
}

#endif