#ifndef _FOOTAGE_LIST_H
#define _FOOTAGE_LIST_H

#include <QTableWidget>
#include <QMenu>
#include <QContextMenuEvent>

namespace studio {
	class FootageListWidget : public QTableWidget {
		Q_OBJECT
	public:
		explicit FootageListWidget(QWidget* parent = Q_NULLPTR);
		~FootageListWidget() {}

		void addFootage(const QList<QUrl>& files);
		bool removeFootage(const QList<QUrl>& files);
		bool hasFootage(const QUrl& file, int& index);

	private slots:
		void onRenameFootage(bool checked);
		void onRemoveFootaage(bool checked);
		void onViewDetail(bool checked);
		void onRevelInShell(bool checked);
		void onStartExport(bool checked);
		void onAddToTimeline(bool checked);
		void onFilesDropped(const QList<QUrl>& files);
		void onEmptyAll(bool checked);

	signals:
		void footageRemoved(const QUrl& file);
		void footageRenamed(const QUrl& oldName, const QUrl& newName);
		void startExportClicked(const QUrl& file);
		void addToTimelineClicked(const QUrl& file); 
		void hoverIndexChanged(const QModelIndex& index);
		void fileOpened(const QUrl& filePath);
		void invalidFilesOpened(const QList<QUrl>& invalidFiles);
		void fileListCleared();
 
	protected:
		void contextMenuEvent(QContextMenuEvent *event) override;
		bool event(QEvent* event) override;
		void dragEnterEvent(QDragEnterEvent *event) override;
		void dragMoveEvent(QDragMoveEvent *event) override;
		void dragLeaveEvent(QDragLeaveEvent *event) override;
		void dropEvent(QDropEvent *event) override;
		void mouseMoveEvent(QMouseEvent* event) override;

	private:
		void initializeTableView();
		void addModelData(int rows, const QUrl& url);
		void removeModelData(const QUrl& url);

	private:
		QMenu* mContextMenu;
		QAction* mRemove;
		QAction* mViewDetail;
		QAction* mAddToTimeline;
		QAction* mStartExport;
		QAction* mRevelInShell;
		QAction* mRename;
		QAction* mEmptyAll;

		QPoint mContextPos;
		QList<QUrl> mImportedList;  
	};
}


#endif
