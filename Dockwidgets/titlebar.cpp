#include "titlebar.h"
 
#include <QHBoxLayout>
#include <QDockWidget>
#include <QStyle>

namespace studio {
	TitleBar::TitleBar(const QString& titleText, QWidget* parent /* = Q_NULLPTR */)
		: QWidget(parent) { 
		setObjectName("dockTitleBar");
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		mainLayout->setSpacing(0);

		title = new QLabel(titleText, this);
		title->setObjectName("dockTitleText");
		closeBtn = new QPushButton(style()->standardIcon(QStyle::SP_TitleBarCloseButton), "", this);
		closeBtn->setFlat(true);
		closeBtn->setToolTip("Close"); 
		closeBtn->setObjectName("dockTitleButton");
		mainLayout->addWidget(title, 0, Qt::AlignLeft); 
		mainLayout->addWidget(closeBtn, 0, Qt::AlignRight);

		connect(closeBtn, &QAbstractButton::clicked, this, &TitleBar::onCloseClicked);
	}

	void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
		QDockWidget *dockWidget = qobject_cast<QDockWidget*>(parentWidget());
		if (dockWidget != nullptr) {
			bool isFloating = dockWidget->isFloating();
			dockWidget->setFloating(!isFloating);
			dockWidget->move(dockWidget->pos().x(), dockWidget->pos().y() + 10);
		} 
	}

	void TitleBar::onCloseClicked() {
		QDockWidget *dockWidget = qobject_cast<QDockWidget*>(parentWidget());
		if (dockWidget != nullptr) {
			dockWidget->hide();
		}
	}
	QSize TitleBar::minimumSizeHint() const {
		QDockWidget* dockWidget = qobject_cast<QDockWidget*>(parentWidget());
		if (dockWidget != nullptr) {
			QSize result(100, 25);
			if (dockWidget->features() & QDockWidget::DockWidgetVerticalTitleBar) {
				result.transpose();
			}
			return result;
		}
	}

	QSize TitleBar::sizeHint() const {
		return minimumSizeHint();
	}

}
