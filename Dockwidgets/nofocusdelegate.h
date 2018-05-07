#ifndef ABSTRACT_NOFOCUSDELEGATE_H
#define ABSTRACT_NOFOCUSDELEGATE_H

#include <QStyledItemDelegate>

namespace studio {

	class AbstractNoFocusDelegate : public QStyledItemDelegate {
		Q_OBJECT
	public:
		enum class FileType {
			RAW,
			INSP,
			INSV,
			UNKNOWN
		};
		explicit AbstractNoFocusDelegate(QObject *parent = Q_NULLPTR);
		~AbstractNoFocusDelegate();
		virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			const QModelIndex &index) const override; 
	protected:
		QStyleOptionViewItem modifyOptionState(const QStyleOptionViewItem& option, const QModelIndex& index) const;
	protected:
		QPoint mMousePoint; 
	};

}


#endif // ABSTRACT_NOFOCUSDELEGATE_H
