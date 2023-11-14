#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QPointF>
#include <QPainter>
#include <QPixmap>

class Projectile {
public:
    Projectile(const QPointF &pos, qreal speedX);
    void update();
    void draw(QPainter *painter) const;
    QRectF boundingRect() const;

private:
    QPointF position;
    qreal speedX;
    QPixmap sprite;
};

#endif // PROJECTILE_H
