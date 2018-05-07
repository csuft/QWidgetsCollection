#include "customtableview.h"  
#include <QMouseEvent>
 
CustomTableView::CustomTableView(QWidget* parent)
	: QTableView(parent)
{ 
}

CustomTableView::~CustomTableView() {

} 

void CustomTableView::mouseMoveEvent(QMouseEvent* event) {
	QModelIndex index = indexAt(event->pos());
	emit hoverIndexChanged(index);
	QTableView::mouseMoveEvent(event);
}