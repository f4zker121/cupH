#include "Player.h"
#include <QRectF>

Player::Player(const QPointF &pos) : position(pos), speedX(0), speedY(0), onGround(true), movingLeft(false), movingRight(false), dashSpeed(6.0), isDashing(false), dashDuration(0) {
    sprite = QPixmap(":/image/image/Cup_Idle.webp");
    sprite = sprite.scaled(QSize(120, 400), Qt::KeepAspectRatio);
}

void Player::update() {
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

    qreal newXPos = position.x() + speedX;

    if (newXPos < 0) {
        newXPos = 0;
    } else if (newXPos > 1000) {
        newXPos = 1000;
    }

    position.setX(newXPos);

    position.setY(position.y() + speedY);

    if (position.y() >= 350) {
        position.setY(350);
        onGround = true;
    } else {
        onGround = false;
    }
}



QPointF Player::getVelocity() const {
    return QPointF(speedX, speedY);
}

void Player::moveLeft() {
    if (position.x() > 0) {
        speedX = -5;
        movingLeft = true;
        movingRight = false;
    }
}

void Player::moveRight() {
    if (position.x() < 1000) {
        speedX = 5;
        movingLeft = false;
        movingRight = true;
    }
}

void Player::stopMoving() {
    speedX = 0;
    movingLeft = false;
    movingRight = false;
}



void Player::setVelocity(const QPointF &velocity) {
    speedX = velocity.x();
    speedY = velocity.y();
}

int Player::facingDirection() const {
    return movingRight ? 1 : -1;
}

QRectF Player::boundingRect() const {
    return QRectF(position, QSizeF(sprite.width(), sprite.height()));
}

void Player::draw(QPainter *painter) {
    QRectF targetRect = boundingRect();
    painter->drawPixmap(targetRect.toRect(), sprite);
}


void Player::jump() {
    if (onGround) {
        speedY = -15;
        onGround = false;
    }
}

void Player::startDash() {
    if (!isDashing) {
        speedX *= dashSpeed;
        isDashing = true;
        dashDuration = 10;
    }
}

void Player::stopDash() {
    if (isDashing) {
        speedX /= dashSpeed;
        isDashing = false;
    }
}

void Player::updateDash() {
    if (isDashing) {
        dashDuration--;
        if (dashDuration <= 0) {
            stopDash();
        }
    }
}
void Player::stopMovingLeft() {
    movingLeft = false;
    if (!movingRight) {
        speedX = 0;
    }
}

void Player::stopMovingRight() {
    movingRight = false;
    if (!movingLeft) {
        speedX = 0;
    }
}

