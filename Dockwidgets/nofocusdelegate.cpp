#include "nofocusdelegate.h"

namespace studio {

	AbstractNoFocusDelegate::AbstractNoFocusDelegate(QObject *parent)
		: QStyledItemDelegate(parent) {

	}

	AbstractNoFocusDelegate::~AbstractNoFocusDelegate() {

	}

	QStyleOptionViewItem AbstractNoFocusDelegate::modifyOptionState(const QStyleOptionViewItem& option,
		const QModelIndex& index) const {
		QStyleOptionViewItem noFocusOption(option);
		// remove the focus state
		if (noFocusOption.state & QStyle::State_HasFocus) {
			noFocusOption.state ^= QStyle::State_HasFocus;
		}  
		return noFocusOption;
	}

	void AbstractNoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const {
        QStyleOptionViewItem op = modifyOptionState(option, index);
        QStyledItemDelegate::paint(painter, op, index);
	}  
}
 
