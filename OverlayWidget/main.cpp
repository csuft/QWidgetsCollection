#ifndef _OVERLAY_H
#define _OVERLAY_H

#include <QWidget> 

namespace video_parser {

	class Overlay : public QWidget {
		Q_OBJECT
	public:
		const int PADDING = 6; 
		enum DRAG_DIRECTION {
			UPPER = 0,
			LOWER = 1,
			LEFT,
			RIGHT,
			LEFTUPPER,
			LEFTLOWER,
			RIGHTLOWER,
			RIGHTUPPER,
			NONE
		};

		Overlay(const QString& id, const QPoint& pos, QWidget* parent = Q_NULLPTR);
		~Overlay() { mIsInit = false; close(); };

	protected:
		DRAG_DIRECTION getRegion(const QPoint &cursor);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		virtual void mouseMoveEvent(QMouseEvent *e);
		virtual void moveEvent(QMoveEvent *);
		virtual void resizeEvent(QResizeEvent *);
		virtual void showEvent(QShowEvent *);
		virtual void hideEvent(QHideEvent *);
		virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);
		virtual void closeEvent(QCloseEvent *);
		virtual void paintEvent(QPaintEvent *);

	public slots:
		void onMouseChange(int x, int y);

	signals:
		void overlayChanged(const QString& overlayId, const QRect& rect);
		void sizeChange(int, int);
		void postionChange(int, int);

	private:
		QString mId;
		QPoint mTopLeft;
		QSize mSize;
		bool mMousePressed; 
		bool mIsInit; 
		DRAG_DIRECTION  mDragDirection; 
		QPoint mOriginPoint;  
		QPoint mMoveOffset; 
		QPolygon mListMarker;
		QRect mCurrentRect;
	};
}

#endif // _OVERLAY_H