#include "footageList.h"

#include <QHeaderView>
#include <QModelIndex>
#include "filelistnofocusdelegate.h"
#include "nofocusdelegate.h"

namespace studio {
	FootageListWidget::FootageListWidget(QWidget* parent /* = Q_NULLPTR */)
		: QTableWidget(parent) {
		mContextMenu = new QMenu(this);
		mContextMenu->setObjectName("footageContextMenu");
		mRemove = new QAction(tr("Remove"), this);
		mViewDetail = new QAction(tr("View Detail"), this);
		mAddToTimeline = new QAction(tr("Add to Timeline"), this);
		mStartExport = new QAction(tr("Start Export"), this);
		mRevelInShell = new QAction(tr("Revel in Shell"), this);
		mRename = new QAction(tr("Rename"), this);
		mEmptyAll = new QAction(tr("Empty All"), this);

		initializeTableView();

		connect(mRename, &QAction::triggered, this, &FootageListWidget::onRenameFootage);
		connect(mViewDetail, &QAction::triggered, this, &FootageListWidget::onViewDetail);
		connect(mAddToTimeline, &QAction::triggered, this, &FootageListWidget::onAddToTimeline);
		connect(mStartExport, &QAction::triggered, this, &FootageListWidget::onStartExport);
		connect(mRevelInShell, &QAction::triggered, this, &FootageListWidget::onRevelInShell);
		connect(mRemove, &QAction::triggered, this, &FootageListWidget::onRemoveFootaage);
	}

	void FootageListWidget::initializeTableView() {  
		horizontalHeader()->setHidden(true);
		horizontalHeader()->setStretchLastSection(true);
		verticalHeader()->setHidden(true); 
		setSortingEnabled(true); 
        setWordWrap(false);
		setMouseTracking(true);
		setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
		setSelectionBehavior(QAbstractItemView::SelectRows);
        setSelectionMode(QAbstractItemView::SingleSelection);
		setEditTriggers(QAbstractItemView::DoubleClicked);
        setItemDelegate(new studio::AbstractNoFocusDelegate());
		setAlternatingRowColors(false); 
	}

	void FootageListWidget::addFootage(const QList<QUrl>& files) {
		int index = -1;
		int rows = 0;
		for (auto it = files.constBegin(); it != files.constEnd(); ++it) {
			if (!hasFootage(*it, index)) {
				mImportedList.push_back(*it);
				rows = rowCount();
				addModelData(rows, *it);
			}
		}
	}

	bool FootageListWidget::removeFootage(const QList<QUrl>& files) {
		int index = -1;
		for (auto it = files.constBegin(); it != files.constEnd(); ++it) {
			if (hasFootage(*it, index)) {
				mImportedList.removeAt(index);
				removeModelData(*it);
			}
		}
		return true;
	}

	bool FootageListWidget::hasFootage(const QUrl& file, int& index) {
		index = -1;
		for (auto i = 0; i < mImportedList.size(); ++i) {
			if (mImportedList.at(i) == file) {
				index = i;
				return true;
			}
		}

		return false;
	}

	void FootageListWidget::onRenameFootage(bool checked) {

	}

	void FootageListWidget::onRemoveFootaage(bool checked) {

	}

	void FootageListWidget::onViewDetail(bool checked) {

	}

    void FootageListWidget::onRevelInShell(bool checked) {
	}

	void FootageListWidget::onStartExport(bool checked) {

	}

	void FootageListWidget::onAddToTimeline(bool checked) {

	}

	void FootageListWidget::onEmptyAll(bool checked) {
		emit fileListCleared();
		clear();
	}

	void FootageListWidget::contextMenuEvent(QContextMenuEvent *event) {
		mContextMenu->clear();
		mContextPos = event->pos();
		QModelIndex currentIndex = this->indexAt(mContextPos);
		// only show popup menu for the second column
		if (currentIndex.isValid() && currentIndex.column() == 1) {
			QPoint mousePoint = event->pos();
			mContextMenu->addAction(mRevelInShell);
			mContextMenu->addAction(mViewDetail);
			mContextMenu->addAction(mRename);
			mContextMenu->addAction(mRemove);
			mContextMenu->addAction(mStartExport);
			mContextMenu->addAction(mAddToTimeline);
		} 

		mContextMenu->exec(QCursor::pos());
		event->accept();
	}

	bool FootageListWidget::event(QEvent* event) {
		if (event->type() == QEvent::ToolTip) {
			QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);

			return true;
		}
		return QTableView::event(event);
	}

	void FootageListWidget::dragEnterEvent(QDragEnterEvent *event) {
		event->acceptProposedAction();
	}
	
	void FootageListWidget::dragMoveEvent(QDragMoveEvent *event) {
		event->acceptProposedAction();
	}
	
	void FootageListWidget::dragLeaveEvent(QDragLeaveEvent *event) {
		event->accept();
	}

	void FootageListWidget::dropEvent(QDropEvent *event) {

		event->acceptProposedAction();
	}

	void FootageListWidget::mouseMoveEvent(QMouseEvent* event) {
		QModelIndex index = indexAt(event->pos());
		emit hoverIndexChanged(index);
		QTableView::mouseMoveEvent(event);
	} 

	void FootageListWidget::onFilesDropped(const QList<QUrl>& files) {

	}

	void FootageListWidget::addModelData(int rows, const QUrl& url) {
		QTableWidgetItem* tableItem = new QTableWidgetItem;
		tableItem->setData(Qt::EditRole, url.toLocalFile());
		tableItem->setText(url.fileName());
		if (url.toLocalFile().toLower().endsWith("dng")) {
			tableItem->setIcon(QIcon(":/default/dng"));
		}
		else if (url.toLocalFile().toLower().endsWith("insp")) {
			tableItem->setIcon(QIcon(":/default/dng"));
		}
		else if (url.toLocalFile().toLower().endsWith("insv")) {
			tableItem->setIcon(QIcon(":/default/dng"));
		}
		else {
			tableItem->setIcon(QIcon(":/default/dng"));
		} 
		setItem(rows, 0, tableItem);
	}

	void FootageListWidget::removeModelData(const QUrl& url) {
		int rows = rowCount();
		QString itemData;
		for (int i = 0; i < rows; ++i) {
			QTableWidgetItem* itemData = takeItem(i, 0);
			if (!itemData->data(Qt::EditRole).toString().compare(url.fileName())) {
				removeRow(i);
				return;
			}
		}
	}
}
