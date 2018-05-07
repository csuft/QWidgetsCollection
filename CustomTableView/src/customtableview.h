#ifndef _CUSTOM_TABLE_VIEW_H
#define _CUSTOM_TABLE_VIEW_H

#include <QTableView>
#include "customitemmodel.h"

class CustomTableView : public QTableView {
	Q_OBJECT
public:
	explicit CustomTableView(QWidget* parent = Q_NULLPTR);
	~CustomTableView();

protected: 
	virtual void mouseMoveEvent(QMouseEvent* event) override;

signals:
	void hoverIndexChanged(const QModelIndex& index);
};
	

#endif // _CUSTOM_TABLE_VIEW_H