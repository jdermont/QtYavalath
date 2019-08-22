#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QColor>
#include <cmath>

class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;

signals:

public slots:
};

#endif // BOARDVIEW_H
