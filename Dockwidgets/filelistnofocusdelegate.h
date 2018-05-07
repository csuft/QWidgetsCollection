#ifndef FILELIST_NOFOCUSDELEGATE_H
#define FILELIST_NOFOCUSDELEGATE_H

#include "nofocusdelegate.h"

#define FILE_TYPE_ICON_WIDTH 32
#define FILE_TYPE_ICON_HEIGHT 20

namespace studio {

	class FileListNoFocusDelegate : public AbstractNoFocusDelegate {
		Q_OBJECT
	public:
		explicit FileListNoFocusDelegate(QObject *parent = Q_NULLPTR);
		~FileListNoFocusDelegate();
		virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			const QModelIndex &index) const override;
		virtual QWidget* createEditor(QWidget * parent, const QStyleOptionViewItem & option,
			const QModelIndex & index) const override;  
	};


}

#endif // FILELIST_NOFOCUSDELEGATE_H
