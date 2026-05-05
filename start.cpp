#include "start.h"
#include "ui_start.h"
#include "gamewidget.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QKeyEvent>

start::start(int rows, int cols, int difficulty, QWidget *parent)
    : QWidget(parent), ui(new Ui::start),
    game(nullptr), m_rows(rows), m_cols(cols), m_difficulty(difficulty)
{
    ui->setupUi(this);
    setFixedSize(1400, 760);
    setStyleSheet("background-color: #3E2723;");
    setWindowTitle("Snake Game");

    buildUI();
    launchGame();
}

void start::buildUI()
{
    // ── Score bar ─────────────────────────────────────────
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    QFont sf;
    sf.setPointSize(18);
    sf.setBold(true);
    scoreLabel->setFont(sf);
    scoreLabel->setStyleSheet("color: #FFD54F; background: transparent;");
    scoreLabel->setGeometry(0, 10, 1400, 36);

    // ── Game Over overlay ─────────────────────────────────
    gameOverLabel = new QLabel(this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet(
        "background-color: rgba(0,0,0,160);"
        "color: #FF5252;"
        "font-size: 38px;"
        "font-weight: bold;"
        "border-radius: 16px;");
    gameOverLabel->hide();

    // ── Restart / Menu buttons ────────────────────────────
    restartBtn = new QPushButton("▶ Play Again", this);
    restartBtn->setStyleSheet(
        "QPushButton { background:#4CAF50; color:white; font-size:16px; "
        "font-weight:bold; border:none; border-radius:10px; padding:10px; }"
        "QPushButton:hover { background:#66BB6A; }");
    restartBtn->hide();
    connect(restartBtn, &QPushButton::clicked, this, &start::onRestart);

    menuBtn = new QPushButton("⏮ Main Menu", this);
    menuBtn->setStyleSheet(
        "QPushButton { background:#1565C0; color:white; font-size:16px; "
        "font-weight:bold; border:none; border-radius:10px; padding:10px; }"
        "QPushButton:hover { background:#1976D2; }");
    menuBtn->hide();
    connect(menuBtn, &QPushButton::clicked, this, &start::onBackToMenu);
}

void start::launchGame()
{
    // Remove old game widget if restarting
    if (game) {
        game->deleteLater();
        game = nullptr;
    }

    game = new GameWidget(m_rows, m_cols, m_difficulty, this);

    int gridW = m_cols * GameWidget::CELL_SIZE;
    int gridH = m_rows * GameWidget::CELL_SIZE;

    int x = (1400 - gridW) / 2;
    int y = (760  - gridH) / 2;
    game->setGeometry(x, y, gridW, gridH);
    game->show();
    game->setFocus();

    connect(game, &GameWidget::scoreChanged, this, &start::onScoreChanged);
    connect(game, &GameWidget::gameOver,     this, &start::onGameOver);

    // Hide overlays
    gameOverLabel->hide();
    restartBtn->hide();
    menuBtn->hide();
    scoreLabel->setText("Score: 0");
}

void start::onScoreChanged(int score)
{
    scoreLabel->setText(QString("Score: %1").arg(score));
}

void start::onGameOver(int score)
{
    int gw = game->width();
    int gh = game->height();
    int gx = game->x();
    int gy = game->y();

    gameOverLabel->setText(QString("GAME OVER\nScore: %1\n\nP — pause  |  R — restart").arg(score));
    gameOverLabel->setGeometry(gx - 20, gy + gh/4, gw + 40, gh / 2);
    gameOverLabel->show();
    gameOverLabel->raise();

    restartBtn->setGeometry(gx + gw/2 - 120, gy + gh - 80, 110, 44);
    menuBtn->setGeometry(   gx + gw/2 + 10,  gy + gh - 80, 110, 44);
    restartBtn->show();
    menuBtn->show();
    restartBtn->raise();
    menuBtn->raise();
}

void start::onRestart()
{
    launchGame();
}

void start::onBackToMenu()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
    this->deleteLater();
}

void start::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R) {
        onRestart();
        return;
    }
    QWidget::keyPressEvent(event);
}

start::~start()
{
    delete ui;
}