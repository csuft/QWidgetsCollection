#include "customitemdelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QToolTip>
#include <QPainter>
#include <QDebug>

TableViewDelegate::TableViewDelegate(CustomTableView *tableView, QWidget* parent)
	: QStyledItemDelegate(parent),
	m_pOpenButton(new QPushButton),
	m_pDeleteButton(new QPushButton),
	m_nSpacing(5),
	m_nWidth(25),
	m_nHeight(20),
	hover_row(-1),
	m_tableView(tableView)
{
	m_pOpenButton->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/images/open);} \
                                 QPushButton:hover {image:url(:/images/openHover);} \
                                 QPushButton:pressed {image:url(:/images/openPress);}");

	m_pDeleteButton->setStyleSheet("QPushButton {border: none; background-color: transparent; image:url(:/images/delete);} \
                                 QPushButton:hover {image:url(:/images/deleteHover);} \
                                 QPushButton:pressed {image:url(:/images/deletePress);}");
	m_list << QStringLiteral("Open") << QStringLiteral("Delete");
}

TableViewDelegate::~TableViewDelegate(){

}

void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QStyleOptionViewItem viewOption(option);
	initStyleOption(&viewOption, index);
	if (option.state.testFlag(QStyle::State_HasFocus))
		viewOption.state = viewOption.state ^ QStyle::State_HasFocus; 
	if (index.row() == hover_row) {
		viewOption.state |= QStyle::State_MouseOver;
	}
	QStyledItemDelegate::paint(painter, viewOption, index);

	if (index.column() == FILE_OPERATE_COLUMN) { 
		int nCount = m_list.count();
		int nHalf = (option.rect.width() - m_nWidth * nCount - m_nSpacing * (nCount - 1)) / 2;
		int nTop = (option.rect.height() - m_nHeight) / 2;

		for (int i = 0; i < nCount; ++i) { 
			QStyleOptionButton button;
			button.rect = QRect(option.rect.left() + nHalf + m_nWidth * i + m_nSpacing * i,
				option.rect.top() + nTop, m_nWidth, m_nHeight);
			button.state |= QStyle::State_Enabled; 

			if (button.rect.contains(m_mousePoint)) {
				if (m_nType == 0) {
					button.state |= QStyle::State_MouseOver; 
				}
				else if (m_nType == 1) {
					button.state |= QStyle::State_Sunken; 
				}
			}

			QWidget *pWidget = (i == 0) ? m_pOpenButton.data() : m_pDeleteButton.data();
			QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, pWidget);
		}
	}
}
 
bool TableViewDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	if (index.column() != FILE_OPERATE_COLUMN)
		return false;

	m_nType = -1;
	bool bRepaint = false;
	QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
	m_mousePoint = pEvent->pos();

	int nCount = m_list.count();
	int nHalf = (option.rect.width() - m_nWidth * nCount - m_nSpacing * (nCount - 1)) / 2;
	int nTop = (option.rect.height() - m_nHeight) / 2;
	 
	QApplication::restoreOverrideCursor();

	for (int i = 0; i < nCount; ++i) {
		QStyleOptionButton button;
		button.rect = QRect(option.rect.left() + nHalf + m_nWidth * i + m_nSpacing * i,
			option.rect.top() + nTop, m_nWidth, m_nHeight);
		 
		if (!button.rect.contains(m_mousePoint))
			continue;

		bRepaint = true;
		switch (event->type()) { 
		case QEvent::MouseMove: { 
			QApplication::setOverrideCursor(Qt::PointingHandCursor);
			m_nType = 0;
			QToolTip::showText(pEvent->globalPos(), m_list.at(i));
			break;
		} 
		case QEvent::MouseButtonPress: {
			m_nType = 1;
			break;
		} 
		case QEvent::MouseButtonRelease: {
			if (i == 0) {
				emit open(index);
			}
			else {
				emit deleteData(index);
			}
			break;
		}
		default:
			break;
		}
	}

	return bRepaint;
}
 
void TableViewDelegate::onHoverIndexChanged(const QModelIndex& index) { 
	hover_row = index.row();
	m_tableView->viewport()->update();
} 