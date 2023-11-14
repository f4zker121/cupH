#ifndef PLAYER_H
#define PLAYER_H

#include <QPointF>
#include <QPixmap>
#include <QPainter>
#include <QRectF>

class Player {
public:
    Player(const QPointF &pos);

    void update();
    QRectF boundingRect() const;
    void draw(QPainter *painter);
    QPointF getVelocity() const;
    void setVelocity(const QPointF &velocity);
    int facingDirection() const;

    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    void stopMovingLeft(); // Добавьте эту строку
    void stopMovingRight(); // Добавьте эту строку


    void startDash();
    void stopDash();
    void updateDash();

private:
    QPointF position;
    QPixmap sprite;
    qreal speedX;
    qreal speedY;
    bool onGround;
    bool movingLeft;
    bool movingRight;
    qreal dashSpeed;
    bool isDashing;
    int dashDuration;
};

#endif // PLAYER_H
