#ifndef _DOCK_TITLE_BAR_H
#define _DOCK_TITLE_BAR_H
 
#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace studio {
	class TitleBar : public QWidget {
		Q_OBJECT
	public:
		explicit TitleBar(const QString& titleText, QWidget* parent = Q_NULLPTR);
		~TitleBar() {}

	protected:
		virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
		virtual QSize minimumSizeHint() const override;
		virtual QSize sizeHint() const override;

	private slots:
		void onCloseClicked();
	private:
		QLabel* title; 
		QPushButton* closeBtn;
	};
}


#endif // _DOCK_TITLE_BAR_H
