#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

start::start(int rows, int cols, int difficulty, QWidget *parent)
    : QWidget(parent), ui(new Ui::start),
    game(nullptr),
    m_rows(rows), m_cols(cols), m_difficulty(difficulty)
{
    ui->setupUi(this);

    setFixedSize(1400, 760);
    setStyleSheet("background-color: #3E2723;");
    setWindowTitle("Snake");

    // ── Score label ───────────────────────────────────────
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setGeometry(0, 8, 1400, 36);
    scoreLabel->setAlignment(Qt::AlignCenter);
    QFont sf; sf.setPointSize(16); sf.setBold(true);
    scoreLabel->setFont(sf);
    scoreLabel->setStyleSheet("color: #FFD54F; background: transparent;");

    // ── Game-over overlay ─────────────────────────────────
    gameOverLabel = new QLabel(this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet(
        "color: #FF5252; font-size: 30px; font-weight: bold;"
        "background: transparent;");
    gameOverLabel->hide();

    // ── Buttons ───────────────────────────────────────────
    restartBtn = new QPushButton("▶  Play Again", this);
    restartBtn->setStyleSheet(
        "QPushButton{background:#4CAF50;color:white;font-size:15px;"
        "font-weight:bold;border:none;border-radius:10px;padding:8px;}"
        "QPushButton:hover{background:#66BB6A;}");
    restartBtn->hide();
    connect(restartBtn, &QPushButton::clicked, this, &start::onRestart);

    menuBtn = new QPushButton("⏮  Main Menu", this);
    menuBtn->setStyleSheet(
        "QPushButton{background:#1565C0;color:white;font-size:15px;"
        "font-weight:bold;border:none;border-radius:10px;padding:8px;}"
        "QPushButton:hover{background:#1976D2;}");
    menuBtn->hide();
    connect(menuBtn, &QPushButton::clicked, this, &start::onBackToMenu);

    spawnGame();
}

// ─────────────────────────────────────────────────────────────────────────────
void start::spawnGame()
{
    if (game) { game->deleteLater(); game = nullptr; }

    gameOverLabel->hide();
    restartBtn->hide();
    menuBtn->hide();
    scoreLabel->setText("Score: 0");

    // Create the widget — it calls setFixedSize internally
    game = new GameWidget(m_rows, m_cols, m_difficulty, this);

    // Center the grid inside the 1400×760 window
    int gridW = m_cols * GameWidget::CELL_SIZE;
    int gridH = m_rows * GameWidget::CELL_SIZE;
    int gx = (1400 - gridW) / 2;
    int gy = (760  - gridH) / 2;
    game->setGeometry(gx, gy, gridW, gridH);
    game->show();
    game->setFocus();

    connect(game, &GameWidget::scoreChanged, this, &start::onScoreChanged);
    connect(game, &GameWidget::gameOver,     this, &start::onGameOver);

    // Overlay label covers the grid area
    gameOverLabel->setGeometry(gx - 10, gy + gridH / 3, gridW + 20, gridH / 3);
}

// ─────────────────────────────────────────────────────────────────────────────
void start::onScoreChanged(int score)
{
    scoreLabel->setText(QString("Score: %1").arg(score));
}

void start::onGameOver(int score)
{
    gameOverLabel->setText(QString("GAME OVER  —  Score: %1\nR = restart    M = menu").arg(score));
    gameOverLabel->show();
    gameOverLabel->raise();

    int gx = game->x(), gy = game->y();
    int gw = game->width(), gh = game->height();

    restartBtn->setGeometry(gx + gw / 2 - 125, gy + gh - 60, 115, 42);
    menuBtn->setGeometry(   gx + gw / 2 + 10,  gy + gh - 60, 115, 42);
    restartBtn->show(); restartBtn->raise();
    menuBtn->show();    menuBtn->raise();
}

void start::onRestart() { spawnGame(); }

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