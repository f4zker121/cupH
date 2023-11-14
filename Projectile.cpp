#include "Projectile.h"

Projectile::Projectile(const QPointF &pos, qreal speedX) : position(pos), speedX(speedX) {
    sprite = QPixmap(":/image/image/bulet");
}

void Projectile::update() {
    position.setX(position.x() + speedX);
}

void Projectile::draw(QPainter *painter) const {
    painter->drawPixmap(position, sprite);
}

QRectF Projectile::boundingRect() const {
    return QRectF(position, QSizeF(sprite.width(), sprite.height()));
}
