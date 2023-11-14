#include "Boss.h"
#include <QRectF>

Boss::Boss(const QPointF &pos) : position(pos), speedY(0), speedX(3.0), onGround(true), direction(1) {
    sprite = QPixmap(":/image/image/Goopy_p2_jump.webp");
    health = 1000;
}

void Boss::update() {
    const qreal gravity = 0.5;
    const qreal maxFallSpeed = 10.0;

    if (!onGround) {
        speedY += gravity;
        if (speedY > maxFallSpeed) {
            speedY = maxFallSpeed;
        }
    } else {
        speedY = 0;
    }

    position.setY(position.y() + speedY);

    if (position.y() >= 300) {
        position.setY(300);
        onGround = true;
        jump();
    } else {
        onGround = false;
    }

    position.setX(position.x() + speedX * direction);

    if (position.x() <= 0) {
        direction = 1;
    } else if (position.x() >= 1000) {
        direction = -1;
    }
    qreal currentSpeedX = speedX;
    if (health <= 500) {
        currentSpeedX *= 1.5;
    }

    position.setX(position.x() + currentSpeedX * direction);
}

void Boss::draw(QPainter *painter) {
    painter->drawPixmap(position, sprite);
}

QRectF Boss::boundingRect() const {
    return QRectF(position, QSizeF(sprite.width(), sprite.height()));
}

int Boss::getHealth() const {
    return health;
}

void Boss::decreaseHealth(int value) {
    health -= value;
    if (health < 0) {
        health = 0;
    }
}
void Boss::takeDamage(int damage) {
    health -= damage;
}

void Boss::jump() {
    if (onGround) {
        speedY = -15;
        onGround = false;
    }
}
