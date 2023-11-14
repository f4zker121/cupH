#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(nullptr)
{
    ui->setupUi(this);
    setFixedSize(1050, 700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if (game == nullptr) {
        game = new Game(this);
        setCentralWidget(game);
    }
    game->startGame();
    game->show();
}


