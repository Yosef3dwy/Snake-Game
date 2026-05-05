#include "gamewidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

GameWidget::GameWidget(int rows, int cols, int difficulty, QWidget *parent)
    : QWidget(parent),
    m_rows(rows), m_cols(cols),
    m_paused(false), m_dead(false)
{
    // Fix size FIRST so paintEvent knows dimensions
    setFixedSize(cols * CELL_SIZE, rows * CELL_SIZE);
    setFocusPolicy(Qt::StrongFocus);

    m_controller = new GameController(rows, difficulty);

    // Speed: Easy=220ms, Medium=140ms, Hard=75ms
    int ms = (difficulty == 1) ? 220 : (difficulty == 3) ? 75 : 140;

    m_timer = new QTimer(this);
    m_timer->setInterval(ms);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::onTick);
    m_timer->start();
}

QPoint GameWidget::cellPos(int row, int col) const
{
    return QPoint(col * CELL_SIZE, row * CELL_SIZE);
}

QRect GameWidget::cellRect(int row, int col) const
{
    return QRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

// ─────────────────────────────────────────────────────────────────────────────
void GameWidget::onTick()
{
    if (m_paused || m_dead) return;

    bool alive = m_controller->runStep();
    emit scoreChanged(m_controller->getScore());

    if (!alive) {
        m_dead = true;
        m_timer->stop();
        emit gameOver(m_controller->getScore());
    }

    update();   // trigger repaint every tick
}

// ─────────────────────────────────────────────────────────────────────────────
void GameWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:    case Qt::Key_W:
        m_controller->changeDirection(Direction::UP);    break;
    case Qt::Key_Down:  case Qt::Key_S:
        m_controller->changeDirection(Direction::DOWN);  break;
    case Qt::Key_Left:  case Qt::Key_A:
        m_controller->changeDirection(Direction::LEFT);  break;
    case Qt::Key_Right: case Qt::Key_D:
        m_controller->changeDirection(Direction::RIGHT); break;
    case Qt::Key_P:
        m_paused = !m_paused;
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, false);

    const QColor sandLight("#E8C88A");
    const QColor sandDark ("#D4A855");
    const QColor gridLine ("#B8882A");
    const QColor borderCol("#5D3A10");

    const QColor snakeBodyCol("#2E7D32");
    const QColor snakeHeadCol("#1B5E20");
    const QColor nFoodCol    ("#E53935");
    const QColor sFoodCol    ("#FF6F00");

    // ── 1. Checkerboard background ────────────────────────
    for (int row = 0; row < m_rows; ++row) {
        for (int col = 0; col < m_cols; ++col) {
            QColor bg = ((row + col) % 2 == 0) ? sandLight : sandDark;
            p.fillRect(cellRect(row, col), bg);
        }
    }

    // ── 2. Board contents (snake body + food) ─────────────
    Board &board = m_controller->board;
    int side = board.getSide();

    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            CellContent c = board[row][col];
            if (c == CellContent::empty) continue;

            QRect r = cellRect(row, col).adjusted(2, 2, -2, -2);

            if (c == CellContent::body) {
                p.setBrush(QBrush(snakeBodyCol));
                p.setPen(QPen(snakeHeadCol, 1));
                p.drawRoundedRect(r, 5, 5);
            }
            else if (c == CellContent::Nfood) {
                p.setBrush(QBrush(nFoodCol));
                p.setPen(Qt::NoPen);
                p.drawEllipse(r);
            }
            else if (c == CellContent::Sfood) {
                p.setBrush(QBrush(sFoodCol));
                p.setPen(QPen(Qt::yellow, 1));
                p.drawEllipse(r);
                // cross marker
                p.setPen(QPen(Qt::white, 2));
                p.drawLine(r.center() + QPoint(0, -r.height()/3),
                           r.center() + QPoint(0,  r.height()/3));
                p.drawLine(r.center() + QPoint(-r.width()/3, 0),
                           r.center() + QPoint( r.width()/3, 0));
            }
        }
    }

    // ── 3. Snake head highlight + eyes ───────────────────
    auto [hx, hy] = m_controller->getHead();  // (col, row)
    QRect hr = cellRect(hy, hx).adjusted(2, 2, -2, -2);
    p.setBrush(QBrush(snakeHeadCol));
    p.setPen(QPen(Qt::black, 1));
    p.drawRoundedRect(hr, 5, 5);
    // eyes
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawEllipse(hr.x() + 5,  hr.y() + 5, 4, 4);
    p.drawEllipse(hr.x() + 14, hr.y() + 5, 4, 4);

    // ── 4. Grid lines ─────────────────────────────────────
    p.setPen(QPen(gridLine, 1));
    int gw = m_cols * CELL_SIZE, gh = m_rows * CELL_SIZE;
    for (int x = 0; x <= m_cols; ++x)
        p.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, gh);
    for (int y = 0; y <= m_rows; ++y)
        p.drawLine(0, y * CELL_SIZE, gw, y * CELL_SIZE);

    // ── 5. Border ─────────────────────────────────────────
    p.setPen(QPen(borderCol, 4));
    p.setBrush(Qt::NoBrush);
    p.drawRect(2, 2, gw - 4, gh - 4);

    // ── 6. Pause / Game-over overlays ────────────────────
    if (m_paused && !m_dead) {
        p.fillRect(rect(), QColor(0, 0, 0, 130));
        p.setPen(Qt::white);
        QFont f; f.setPointSize(22); f.setBold(true);
        p.setFont(f);
        p.drawText(rect(), Qt::AlignCenter, "PAUSED\nPress P to resume");
    }
    if (m_dead) {
        p.fillRect(rect(), QColor(0, 0, 0, 160));
        p.setPen(QColor("#FF5252"));
        QFont f; f.setPointSize(26); f.setBold(true);
        p.setFont(f);
        p.drawText(rect(), Qt::AlignCenter,
                   QString("GAME OVER\nScore: %1").arg(m_controller->getScore()));
    }
}