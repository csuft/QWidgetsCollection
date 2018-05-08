#include "customrubberband.h"

#include <QPainter>
#include <QStyleOptionRubberBand>

CustomRubberBand::CustomRubberBand(Shape s, QWidget* parent)
    : QRubberBand(s, parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
}

void CustomRubberBand::paintEvent(QPaintEvent *event)
{
    QRubberBand::paintEvent(event);

    QStyleOptionRubberBand styleOption;
    styleOption.opaque = true;
    initStyleOption(&styleOption);
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.drawText(rect().adjusted(5, 5, 0, 0), Qt::AlignLeft | Qt::AlignTop, QString("%1x%2+%3+%4").arg(rect().width()).arg(rect().height()).arg(rect().left()).arg(rect().top()));

}
