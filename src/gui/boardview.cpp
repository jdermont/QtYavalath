#include "boardview.h"

BoardView::BoardView(QWidget *parent) : QWidget(parent)
{

}

QSize BoardView::sizeHint() const {
    return QSize(500, 500);
}

QSize BoardView::minimumSizeHint() const {
    return QSize(300, 300);
}

void BoardView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.fillRect(0, 0, width(), height(), QBrush(QColor("red")));

    int marginX = 50;
    int marginY = 50;
    qreal side = 30;
    qreal dx = sqrt(3)/2 * side;
    qreal m = side * sqrt(3);
    qreal n = 1.5 * side;

    for (int i=0; i < 5; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 4 * dx, marginY + -side/2)
                << QPointF(marginX + i*m + 0 + 4 * dx, marginY + -side)
                << QPointF(marginX + i*m + -dx + 4 * dx, marginY + -side/2)
                << QPointF(marginX + i*m + -dx + 4 * dx, marginY + side/2)
                << QPointF(marginX + i*m + 0 + 4 * dx, marginY + side)
                << QPointF(marginX + i*m + dx + 4 * dx, marginY + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 6; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 3 * dx, marginY + n + -side/2)
                << QPointF(marginX + i*m + 0 + 3 * dx, marginY + n + -side)
                << QPointF(marginX + i*m + -dx + 3 * dx, marginY + n + -side/2)
                << QPointF(marginX + i*m + -dx + 3 * dx, marginY + n + side/2)
                << QPointF(marginX + i*m + 0 + 3 * dx, marginY + n + side)
                << QPointF(marginX + i*m + dx + 3 * dx, marginY + n + side/2);

        QBrush brush2(Qt::gray, Qt::BrushStyle::SolidPattern);
        painter.setBrush(brush2);
        painter.drawPolygon(polygon);
        painter.setBrush(brush);
    }

    for (int i=0; i < 7; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 2 * dx, marginY + 2 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 2 * dx, marginY + 2 * n + -side)
                << QPointF(marginX + i*m + -dx + 2 * dx, marginY + 2 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 2 * dx, marginY + 2 * n + side/2)
                << QPointF(marginX + i*m + 0 + 2 * dx, marginY + 2 * n + side)
                << QPointF(marginX + i*m + dx + 2 * dx, marginY + 2 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 8; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 1 * dx, marginY + 3 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 1 * dx, marginY + 3 * n + -side)
                << QPointF(marginX + i*m + -dx + 1 * dx, marginY + 3 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 1 * dx, marginY + 3 * n + side/2)
                << QPointF(marginX + i*m + 0 + 1 * dx, marginY + 3 * n + side)
                << QPointF(marginX + i*m + dx + 1 * dx, marginY + 3 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 9; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx, marginY + 4 * n + -side/2)
                << QPointF(marginX + i*m + 0, marginY + 4 * n + -side)
                << QPointF(marginX + i*m + -dx, marginY + 4 * n + -side/2)
                << QPointF(marginX + i*m + -dx, marginY + 4 * n + side/2)
                << QPointF(marginX + i*m + 0, marginY + 4 * n + side)
                << QPointF(marginX + i*m + dx, marginY + 4 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 8; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 1 * dx, marginY + 5 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 1 * dx, marginY + 5 * n + -side)
                << QPointF(marginX + i*m + -dx + 1 * dx, marginY + 5 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 1 * dx, marginY + 5 * n + side/2)
                << QPointF(marginX + i*m + 0 + 1 * dx, marginY + 5 * n + side)
                << QPointF(marginX + i*m + dx + 1 * dx, marginY + 5 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 7; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 2 * dx, marginY + 6 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 2 * dx, marginY + 6 * n + -side)
                << QPointF(marginX + i*m + -dx + 2 * dx, marginY + 6 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 2 * dx, marginY + 6 * n + side/2)
                << QPointF(marginX + i*m + 0 + 2 * dx, marginY + 6 * n + side)
                << QPointF(marginX + i*m + dx + 2 * dx, marginY + 6 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 6; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 3 * dx, marginY + 7 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 3 * dx, marginY + 7 * n + -side)
                << QPointF(marginX + i*m + -dx + 3 * dx, marginY + 7 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 3 * dx, marginY + 7 * n + side/2)
                << QPointF(marginX + i*m + 0 + 3 * dx, marginY + 7 * n + side)
                << QPointF(marginX + i*m + dx + 3 * dx, marginY + 7 * n + side/2);

        painter.drawPolygon(polygon);
    }

    for (int i=0; i < 5; i++) {
        QPolygonF polygon;
        polygon
                // standing on a point
                << QPointF(marginX + i*m + dx + 4 * dx, marginY + 8 * n + -side/2)
                << QPointF(marginX + i*m + 0 + 4 * dx, marginY + 8 * n + -side)
                << QPointF(marginX + i*m + -dx + 4 * dx, marginY + 8 * n + -side/2)
                << QPointF(marginX + i*m + -dx + 4 * dx, marginY + 8 * n + side/2)
                << QPointF(marginX + i*m + 0 + 4 * dx, marginY + 8 * n + side)
                << QPointF(marginX + i*m + dx + 4 * dx, marginY + 8 * n + side/2);

        painter.drawPolygon(polygon);
    }

//    QPolygonF polygon;
////    qreal dx = sqrt(3)/2 * side;
//    polygon
//            // standing on a point
//            << QPointF(marginX + dx, marginY + -side/2)
//            << QPointF(marginX + 0, marginY + -side)
//            << QPointF(marginX + -dx, marginY + -side/2)
//            << QPointF(marginX + -dx, marginY + side/2)
//            << QPointF(marginX + 0, marginY + side)
//            << QPointF(marginX + dx, marginY + side/2);
//    // Sitting flat
//    //            << QPointF(-side/2, dx)
//    //            << QPointF(-side, 0)
//    //            << QPointF(-side/2, -dx)
//    //            << QPointF(side/2, -dx)
//    //            << QPointF(side, 0)
//    //            << QPointF(side/2, dx);

//    qreal xx = side * sqrt(3);
//    QPolygonF polygon2;
//    polygon2
//            // standing on a point
//            << QPointF(marginX + xx + dx, marginY + -side/2)
//            << QPointF(marginX + xx + 0, marginY + -side)
//            << QPointF(marginX + xx + -dx, marginY + -side/2)
//            << QPointF(marginX + xx + -dx, marginY + side/2)
//            << QPointF(marginX + xx + 0, marginY + side)
//            << QPointF(marginX + xx + dx, marginY + side/2);

//    QPolygonF polygon3;
//    polygon3
//            // standing on a point
//            << QPointF(186 + dx, 250 + -side/2)
//            << QPointF(186 + 0, 250 + -side)
//            << QPointF(186 + -dx, 250 + -side/2)
//            << QPointF(186 + -dx, 250 + side/2)
//            << QPointF(186 + 0, 250 + side)
//            << QPointF(186 + dx, 250 + side/2);

//    painter.drawPolygon(polygon);
//    painter.drawPolygon(polygon2);
}
