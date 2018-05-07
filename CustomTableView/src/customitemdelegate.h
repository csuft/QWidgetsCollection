#pragma once

#include <QStyledItemDelegate>
#include <QPushButton>
#include "customtableview.h"

#define FILE_OPERATE_COLUMN 2

class TableViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit TableViewDelegate(CustomTableView *tableView, QWidget* parent = 0);
	~TableViewDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

signals:
	void open(const QModelIndex &index);
	void deleteData(const QModelIndex &index);

public slots: 
	void onHoverIndexChanged(const QModelIndex& index);

private:
	QPoint m_mousePoint; 
	QScopedPointer<QPushButton> m_pOpenButton;
	QScopedPointer<QPushButton> m_pDeleteButton;
	QStringList m_list;
	CustomTableView* m_tableView;
	int m_nSpacing; 
	int m_nWidth;  
	int m_nHeight; 
	int m_nType; 
	int hover_row;
};