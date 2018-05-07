#include "filelistnofocusdelegate.h"

#include <QPainter>
#include <QLineEdit>

namespace studio {

	FileListNoFocusDelegate::FileListNoFocusDelegate(QObject *parent)
		: AbstractNoFocusDelegate(parent)  {

	}

	FileListNoFocusDelegate::~FileListNoFocusDelegate() {

	} 

	void FileListNoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const {  
		QStyleOptionViewItem noFocusOption = modifyOptionState(option, index); 
		AbstractNoFocusDelegate::paint(painter, option, index);
	}

	QWidget* FileListNoFocusDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option,
		const QModelIndex & index) const { 
		QLineEdit* editor = new QLineEdit(parent);
		editor->setAlignment(Qt::AlignLeft);

		return editor;
	}
}
