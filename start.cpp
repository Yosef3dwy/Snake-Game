#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"
#include <QFont>

start::start(int rows, int cols, int difficulty, int volume, bool dropTiles, QWidget *parent)
    : QWidget(parent), ui(new Ui::start),
      game(nullptr),
      m_rows(rows), m_cols(cols), m_difficulty(difficulty),
      m_volume(volume), m_dropTiles(dropTiles)
{
    ui->setupUi(this);
    setFixedSize(1400, 760);
    setStyleSheet("background-color: #3E2723;");
    setWindowTitle("Snake");

    // score label
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setGeometry(0, 8, 1400, 36);
    scoreLabel->setAlignment(Qt::AlignCenter);
    QFont sf; sf.setPointSize(16); sf.setBold(true);
    scoreLabel->setFont(sf);
    scoreLabel->setStyleSheet("color: #FFD54F; background: transparent;");

    // game over text
    gameOverLabel = new QLabel(this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet(
        "color: #FF5252; font-size: 28px; font-weight: bold;"
        "background: transparent;");
    gameOverLabel->hide();

    // buttons
    restartBtn = new QPushButton("▶  Play Again", this);
    restartBtn->setStyleSheet(
        "QPushButton{background:#4CAF50;color:white;font-size:14px;"
        "font-weight:bold;border:none;border-radius:10px;padding:8px;}"
        "QPushButton:hover{background:#66BB6A;}");
    restartBtn->hide();
    connect(restartBtn, &QPushButton::clicked, this, &start::onRestart);

    menuBtn = new QPushButton("⏮  Main Menu", this);
    menuBtn->setStyleSheet(
        "QPushButton{background:#1565C0;color:white;font-size:14px;"
        "font-weight:bold;border:none;border-radius:10px;padding:8px;}"
        "QPushButton:hover{background:#1976D2;}");
    menuBtn->hide();
    connect(menuBtn, &QPushButton::clicked, this, &start::onBackToMenu);

    spawnGame();
}

void start::spawnGame()
{
    if (game) { game->deleteLater(); game = nullptr; }

    gameOverLabel->hide();
    restartBtn->hide();
    menuBtn->hide();
    scoreLabel->setText("Score: 0");

    game = new GameWidget(m_rows, m_cols, m_difficulty, m_volume, m_dropTiles, this);

    // center grid in the 1400×760 window
    int gridW = m_cols * GameWidget::CELL_SIZE;
    int gridH = m_rows * GameWidget::CELL_SIZE;
    int gx = (1400 - gridW) / 2;
    int gy = (760  - gridH) / 2;
    game->setGeometry(gx, gy, gridW, gridH);
    game->show();
    game->setFocus();

    connect(game, &GameWidget::scoreChanged, this, &start::onScoreChanged);
    connect(game, &GameWidget::gameOver,     this, &start::onGameOver);

    gameOverLabel->setGeometry(gx - 10, gy + gridH / 3, gridW + 20, gridH / 3);
}

void start::onScoreChanged(int score)
{
    scoreLabel->setText(QString("Score: %1").arg(score));
}

void start::onGameOver(int score)
{
    int gx = game->x(), gy = game->y();
    int gw = game->width(), gh = game->height();

    restartBtn->setGeometry(gx + gw / 2 - 130, gy + gh - 60, 120, 44);
    menuBtn->setGeometry(   gx + gw / 2 + 10,  gy + gh - 60, 120, 44);
    restartBtn->show(); restartBtn->raise();
    menuBtn->show();    menuBtn->raise();
}

void start::onRestart()    { spawnGame(); }

void start::onBackToMenu()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    close();
    deleteLater();
}

void start::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_R) { onRestart();    return; }
    if (ev->key() == Qt::Key_M) { onBackToMenu(); return; }
    QWidget::keyPressEvent(ev);
}

start::~start() { delete ui; }
