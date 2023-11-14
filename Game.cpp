#include "Game.h"
#include <QBrush>
#include <QPen>

Game::Game(QWidget *parent) : QWidget(parent), player(QPointF(100, 350)), boss(QPointF(500, 350)), playerLives(3), gameState(GameState::Playing) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::gameLoop);
    resize(800, 600);
    timer->start(1000 / 60);
    setFocusPolicy(Qt::StrongFocus);
    background = QPixmap(":/image/image/360_F_342419172_SeCpFLBSAhasGKjahiYtVAwiwZ1KjMC2.jpg");
    invincibilityTimer = new QTimer(this);
    connect(invincibilityTimer, &QTimer::timeout, this, &Game::disableInvincibility);
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        player.moveLeft();
    } else if (event->key() == Qt::Key_Right) {
        player.moveRight();
    } else if (event->key() == Qt::Key_Up) {
        player.jump();
    } else if (event->key() == Qt::Key_Z) {
        qreal projectileSpeed = 10.0 * player.facingDirection();
        projectiles.push_back(Projectile(player.boundingRect().center(), projectileSpeed));
    } else if (event->key() == Qt::Key_Shift) {
        player.startDash();
    }
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        player.stopMovingLeft();
    } else if (event->key() == Qt::Key_Right) {
        player.stopMovingRight();
    }
}

void Game::activateInvincibility() {
    invincibilityTimer->start(invincibilityDuration);
}

void Game::disableInvincibility() {
    invincibilityTimer->stop();
}

void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter.setRenderHint(QPainter::Antialiasing);

    player.draw(&painter);
    boss.draw(&painter);

    for (const Projectile &projectile : projectiles) {
        projectile.draw(&painter);
    }

    updateLivesDisplay();
}

void Game::gameLoop() {
    if (gameState != GameState::Playing) {
        return;
    }

    player.update();
    player.updateDash();
    boss.update();

    for (Projectile &projectile : projectiles) {
        projectile.update();
    }

    checkCollisions();
    checkProjectileCollisions();

    if (playerLives <= 0) {
        gameState = GameState::GameOver;
    }

    if (boss.getHealth() <= 0) {
        gameState = GameState::Victory;
    }

    update();
}

void Game::checkCollisions() {
    if (!invincibilityTimer->isActive() && player.boundingRect().intersects(boss.boundingRect())) {
        playerLives--;
        activateInvincibility();
    }
}

void Game::checkProjectileCollisions() {
    for (int i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i].boundingRect().intersects(boss.boundingRect())) {
            boss.takeDamage(10);
            projectiles.remove(i);
            i--;
        }
    }
}
void Game::updateLivesDisplay() {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Arial", 12, QFont::Bold);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("Lives: %1").arg(playerLives));

    painter.drawText(10, 40, QString("Boss Health: %1").arg(boss.getHealth()));

    if (gameState == GameState::GameOver) {
        QFont gameOverFont("Arial", 24, QFont::Bold);
        painter.setFont(gameOverFont);
        painter.setPen(Qt::red);
        painter.drawText(width() / 2 - 100, height() / 2, "Game Over");
    } else if (gameState == GameState::Victory) {
        QFont victoryFont("Arial", 24, QFont::Bold);
        painter.setFont(victoryFont);
        painter.setPen(Qt::green);
        painter.drawText(width() / 2 - 100, height() / 2, "Victory");
    }
}

void Game::startGame(){
    gameLoop();
}

