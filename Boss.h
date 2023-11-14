#pragma once

#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QPixmap>

class Boss {
public:
    Boss(const QPointF &pos);
    QRectF boundingRect() const;
    void draw(QPainter *painter);
    void update();
    void takeDamage(int damage);
    void jump();
    int getHealth() const;
    void decreaseHealth(int value);

private:
    QPointF position;
    QPixmap sprite;
    qreal speedY;
    qreal speedX;
    bool onGround;
    int direction;
    int health;
};
