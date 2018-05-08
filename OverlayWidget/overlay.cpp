#include "overlay.h" 

#include <QMouseEvent>
#include <QPen>
#include <QPainter> 

Overlay::Overlay(const QString& id, const QPoint& pos, QWidget* parent /* = Q_NULLPTR */)
	: QWidget(parent),
	mId(id),
	mMousePressed(false),
	mOriginPoint(pos),
	mDragDirection(NONE) {
	setMouseTracking(true);
	resize(100, 50); 
	move(pos.x(), pos.y());
} 

Overlay::DRAG_DIRECTION Overlay::getRegion(const QPoint &cursor) {
	if (!mIsInit) {
		return NONE;
	}
	DRAG_DIRECTION dragDirection = NONE;
	// left upper
	QPoint pt_lu = mapToParent(rect().topLeft());
	// right lower
	QPoint pt_rl = mapToParent(rect().bottomRight());

	int x = cursor.x();
	int y = cursor.y();
		 
	if (pt_lu.x() + PADDING >= x
		&& pt_lu.x() <= x
		&& pt_lu.y() + PADDING >= y
		&& pt_lu.y() <= y) {
		// ×óÉÏ½Ç
		dragDirection = LEFTUPPER;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x >= pt_rl.x() - PADDING
		&& x <= pt_rl.x()
		&& y >= pt_rl.y() - PADDING
		&& y <= pt_rl.y()) {
		// ÓÒÏÂ½Ç
		dragDirection = RIGHTLOWER;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= pt_lu.x() + PADDING
		&& x >= pt_lu.x()
		&& y >= pt_rl.y() - PADDING
		&& y <= pt_rl.y()) {
		// ×óÏÂ½Ç
		dragDirection = LEFTLOWER;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= pt_rl.x()
		&& x >= pt_rl.x() - PADDING
		&& y >= pt_lu.y()
		&& y <= pt_lu.y() + PADDING) {
		// ÓÒÉÏ½Ç
		dragDirection = RIGHTUPPER;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= pt_lu.x() + PADDING
		&& x >= pt_lu.x()) {
		// ×ó±ß
		dragDirection = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= pt_rl.x()
		&& x >= pt_rl.x() - PADDING) {
		// ÓÒ±ß
		dragDirection = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= pt_lu.y()
		&& y <= pt_lu.y() + PADDING) {
		// ÉÏ±ß
		dragDirection = UPPER;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= pt_rl.y()
		&& y >= pt_rl.y() - PADDING) {
		// ÏÂ±ß
		dragDirection = LOWER;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// Ä¬ÈÏ
		dragDirection = NONE;
		this->setCursor(QCursor(Qt::SizeAllCursor));
	}
	return dragDirection;
}

void Overlay::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		mMousePressed = true;
		if (mDragDirection != NONE) {
			this->mouseGrabber();
		}
		mMoveOffset = e->pos();
	}
}

void Overlay::mouseReleaseEvent(QMouseEvent * e) {
	if (e->button() == Qt::LeftButton) {
		mMousePressed = false;
		if (mDragDirection != NONE) {
			setCursor(QCursor(Qt::SizeAllCursor));
		}
	}
	else if (e->button() == Qt::RightButton) {
		close();
	}
}

void Overlay::mouseMoveEvent(QMouseEvent * e) {
	QPoint mousePoint = mapToParent(e->pos());
	// left upper
	QPoint pt_lu = mapToParent(rect().topLeft());
	// left lower
	QPoint pt_ll = mapToParent(rect().bottomLeft());
	// right lower
	QPoint pt_rl = mapToParent(rect().bottomRight());
	// right upper
	QPoint pt_ru = mapToParent(rect().topRight());
	if (!mMousePressed) { 
		mDragDirection = getRegion(mousePoint);
			 
		switch (mDragDirection) {
		case NONE:
		case RIGHT:
		case RIGHTLOWER:
			mOriginPoint = pt_lu;
			break;
		case RIGHTUPPER:
			mOriginPoint = pt_ll;
			break;
		case LEFT:
		case LEFTLOWER:
			mOriginPoint = pt_ru;
			break;
		case LEFTUPPER:
		case UPPER:
			mOriginPoint = pt_rl;
			break;
		case LOWER:
			mOriginPoint = pt_lu;
			break;
		}
	}
	else {
		if (mDragDirection != NONE) {
			const int& mouse_x = mousePoint.x(); 
			switch (mDragDirection) {
			case LEFT:
				return onMouseChange(mouse_x, pt_ll.y() + 1);
			case RIGHT:
				return onMouseChange(mouse_x, pt_rl.y() + 1);
			case UPPER:
				return onMouseChange(pt_lu.x(), mousePoint.y());
			case LOWER:
				return onMouseChange(pt_rl.x() + 1, mousePoint.y());
			case LEFTUPPER:
			case RIGHTUPPER:
			case LEFTLOWER:
			case RIGHTLOWER:
				return onMouseChange(mouse_x, mousePoint.y());
			default:
				break;
			}
		}
		else {
			move(mapToParent(e->pos() - mMoveOffset)); 
		}
	}
	mCurrentRect = geometry();
}

void Overlay::moveEvent(QMoveEvent *) {
	emit postionChange(x(), y());
}

void Overlay::resizeEvent(QResizeEvent *) {
	mListMarker.clear();
		 
	// ½Çµã
	mListMarker.push_back(QPoint(0, 0));
	mListMarker.push_back(QPoint(width(), 0));
	mListMarker.push_back(QPoint(0, height()));
	mListMarker.push_back(QPoint(width(), height()));

	// ÖÐµã
	mListMarker.push_back(QPoint((width() >> 1), 0));
	mListMarker.push_back(QPoint((width() >> 1), height()));
	mListMarker.push_back(QPoint(0, (height() >> 1)));
	mListMarker.push_back(QPoint(width(), (height() >> 1)));

	emit sizeChange(width(), height());
}

void Overlay::showEvent(QShowEvent *) {
	mIsInit = true;
}

void Overlay::hideEvent(QHideEvent *) {
	mCurrentRect = {};
	mMoveOffset = {};
	mOriginPoint = {};
	mIsInit = false;
}

void Overlay::enterEvent(QEvent *e) {
	setCursor(Qt::SizeAllCursor);
	QWidget::enterEvent(e);
}

void Overlay::leaveEvent(QEvent *e) {
	setCursor(Qt::ArrowCursor);
	QWidget::leaveEvent(e);
}

void Overlay::closeEvent(QCloseEvent *) {
	mIsInit = false;
}

void Overlay::paintEvent(QPaintEvent *) {
	QPainter painter(this);
		 
	QPen pen(QColor(0, 174, 255), 2);
	painter.setPen(pen);
	painter.drawRect(rect());
		 
	pen.setWidth(4);
	pen.setColor(Qt::red);
	painter.setPen(pen);
	painter.drawPoints(mListMarker);
}

void Overlay::onMouseChange(int x, int y) {
	show();
	if (x < 0 || y < 0) {
		return;
	}
	const int& rx = (x >= mOriginPoint.x()) ? mOriginPoint.x() : x;
	const int& ry = (y >= mOriginPoint.y()) ? mOriginPoint.y() : y;
	const int& rw = abs(x - mOriginPoint.x());
	const int& rh = abs(y - mOriginPoint.y());
		 
	mCurrentRect = QRect(rx, ry, rw, rh);
	this->setGeometry(mCurrentRect); 
	parentWidget()->update();
}