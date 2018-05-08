#ifndef CUSTOMRUBBERBAND_H
#define CUSTOMRUBBERBAND_H

#include <QRubberBand>

class CustomRubberBand : public QRubberBand
{
public:
    CustomRubberBand(Shape s, QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // CUSTOMRUBBERBAND_H
