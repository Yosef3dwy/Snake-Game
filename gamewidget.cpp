#include "gamewidget.h"
#include <QPainter>
#include <QKeyEvent>

GameWidget::GameWidget(int r, int c, int difficulty, QWidget *parent)
    : QWidget(parent), m_rows(r), m_cols(c), m_running(true), m_dead(false)
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(c * CELL_SIZE, r * CELL_SIZE);

    m_controller = new GameController(r, difficulty);

    // Timer interval by difficulty: 1=Easy 200ms, 2=Medium 130ms, 3=Hard 70ms
    int interval = 200;
    if (difficulty == 2) interval = 130;
    else if (difficulty == 3) interval = 70;

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::onTick);
    m_timer->start(interval);
}

QPoint GameWidget::cellPos(int row, int col) const
{
    return QPoint(col * CELL_SIZE, row * CELL_SIZE);
}

QRect GameWidget::cellRect(int row, int col) const
{
    return QRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

int GameWidget::getScore() const
{
    return m_controller->board.getSide(); // placeholder; actual score via snake
}

void GameWidget::onTick()
{
    if (!m_running || m_dead) return;

    bool alive = m_controller->runStep();
    emit scoreChanged(m_controller->getScore());

    if (!alive) {
        m_dead = true;
        m_timer->stop();
        emit gameOver(m_controller->getScore());
    }

    update();
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if (m_dead) return;

    switch (event->key()) {
    case Qt::Key_Up:    case Qt::Key_W: m_controller->changeDirection(Direction::UP);    break;
    case Qt::Key_Down:  case Qt::Key_S: m_controller->changeDirection(Direction::DOWN);  break;
    case Qt::Key_Left:  case Qt::Key_A: m_controller->changeDirection(Direction::LEFT);  break;
    case Qt::Key_Right: case Qt::Key_D: m_controller->changeDirection(Direction::RIGHT); break;
    case Qt::Key_P:
        if (m_running) { m_timer->stop();  m_running = false; }
        else           { m_timer->start(); m_running = true;  }
        break;
    default: QWidget::keyPressEvent(event); break;
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    const QColor sandLight("#E8C88A");
    const QColor sandDark ("#D4A855");
    const QColor gridLine ("#B8882A");
    const QColor borderCol("#7A4F1E");
    const QColor shadowCol("#C49A3A");
    const QColor snakeCol ("#2E7D32");
    const QColor snakeHead("#1B5E20");
    const QColor nfoodCol ("#E53935");
    const QColor sfoodCol ("#FF6F00");

    int gridW = m_cols * CELL_SIZE;
    int gridH = m_rows * CELL_SIZE;

    // Draw checkerboard
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            QRect cell = cellRect(row, col);
            QColor base = ((row + col) % 2 == 0) ? sandLight : sandDark;
            painter.fillRect(cell, base);
            painter.setPen(QPen(shadowCol, 1));
            painter.drawLine(cell.bottomLeft(), cell.bottomRight());
            painter.drawLine(cell.topRight(),   cell.bottomRight());
        }
    }

    // Draw board contents
    Board &board = m_controller->board;
    int side = board.getSide();
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            CellContent cell = board[row][col];
            if (cell == CellContent::empty) continue;

            QRect rect = cellRect(row, col).adjusted(2, 2, -2, -2);

            if (cell == CellContent::body) {
                painter.setBrush(snakeCol);
                painter.setPen(QPen(snakeHead, 1));
                painter.drawRoundedRect(rect, 4, 4);
            } else if (cell == CellContent::Nfood) {
                painter.setBrush(nfoodCol);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(rect);
            } else if (cell == CellContent::Sfood) {
                painter.setBrush(sfoodCol);
                painter.setPen(QPen(Qt::yellow, 1));
                // Draw a star shape via polygon
                QRect sr = rect.adjusted(2, 2, -2, -2);
                painter.drawEllipse(sr);
                // Inner star marker
                painter.setPen(QPen(Qt::white, 2));
                painter.drawLine(sr.center() + QPoint(0, -sr.height()/3),
                                 sr.center() + QPoint(0,  sr.height()/3));
                painter.drawLine(sr.center() + QPoint(-sr.width()/3, 0),
                                 sr.center() + QPoint( sr.width()/3, 0));
            }
        }
    }

    // Draw snake head highlight
    auto head = m_controller->getHead();
    QRect headRect = cellRect(head.second, head.first).adjusted(2, 2, -2, -2);
    painter.setBrush(snakeHead);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRoundedRect(headRect, 4, 4);
    // Eyes
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    int ew = 4, eh = 4;
    painter.drawEllipse(headRect.x() + 5,  headRect.y() + 5,  ew, eh);
    painter.drawEllipse(headRect.x() + 14, headRect.y() + 5,  ew, eh);

    // Grid lines
    painter.setPen(QPen(gridLine, 1));
    for (int x = 0; x <= m_cols; x++)
        painter.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, gridH);
    for (int y = 0; y <= m_rows; y++)
        painter.drawLine(0, y * CELL_SIZE, gridW, y * CELL_SIZE);

    // Border
    painter.setPen(QPen(borderCol, 4));
    painter.drawRect(1, 1, gridW - 2, gridH - 2);

    // Game Over overlay
    if (m_dead) {
        painter.fillRect(rect(), QColor(0, 0, 0, 150));
        painter.setPen(Qt::white);
        QFont f = painter.font();
        f.setPointSize(24);
        f.setBold(true);
        painter.setFont(f);
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    }
}