#include "gamewidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDir>
#include <QUrl>

GameWidget::GameWidget(int rows, int cols, int difficulty, int volume, bool dropTiles, QWidget *parent)
    : QWidget(parent),
      m_rows(rows), m_cols(cols),
      m_paused(false), m_dead(false)
{
    setFixedSize(cols * CELL_SIZE, rows * CELL_SIZE);
    setFocusPolicy(Qt::StrongFocus);

    m_controller = new GameController(rows, difficulty, dropTiles);

    // speed select Easy=220ms Medium=140ms Hard=75ms
    int ms = (difficulty == 1) ? 220 : (difficulty == 3) ? 75 : 140;
    m_timer = new QTimer(this);
    m_timer->setInterval(ms);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::onTick);
    m_timer->start();

    // sound effect
    m_eatSound = new QSoundEffect(this);
    m_eatSound->setSource(QUrl::fromLocalFile(QDir::currentPath() + "/eat.wav"));
    m_eatSound->setVolume(volume / 100.0f);

    connect(m_controller, &GameController::foodEaten, this, [this]() {
        m_eatSound->play();
    });
}

void GameWidget::setEatVolume(int value)
{
    m_eatSound->setVolume(value / 100.0f);
}

QPoint GameWidget::cellPos(int row, int col) const
{
    return QPoint(col * CELL_SIZE, row * CELL_SIZE);
}

QRect GameWidget::cellRect(int row, int col) const
{
    return QRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
}

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

    update();
}

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
            update();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, false);

    // ── Palette ───────────────────────────────────────────
    const QColor sandLight ("#E8C88A");
    const QColor sandDark  ("#D4A855");
    const QColor gridLine  ("#B8882A");
    const QColor borderCol ("#5D3A10");
    const QColor snakeBody ("#2E7D32");
    const QColor snakeHead ("#1B5E20");
    const QColor nFoodCol  ("#E53935");
    const QColor sFoodCol  ("#FF6F00");

    for (int row = 0; row < m_rows; ++row)
        for (int col = 0; col < m_cols; ++col)
            p.fillRect(cellRect(row, col),
                       ((row + col) % 2 == 0) ? sandLight : sandDark);

    Board &board = m_controller->board;
    int side = board.getSide();

    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            CellContent c = board[row][col];
            if (c == empty) continue;

            QRect r = cellRect(row, col).adjusted(2, 2, -2, -2);

            if (c == body) {
                p.setBrush(QBrush(snakeBody));
                p.setPen(QPen(snakeHead, 1));
                p.drawRoundedRect(r, 5, 5);
            }
            else if (c == Nfood) {
                p.setBrush(QBrush(nFoodCol));
                p.setPen(Qt::NoPen);
                p.drawEllipse(r);
            }
            else if (c == Sfood) {
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
            else if (c == dropped) {
                // Dark cracked-stone tile
                QRect tr = cellRect(row, col).adjusted(1, 1, -1, -1);
                p.setBrush(QBrush(QColor("#37474F")));
                p.setPen(Qt::NoPen);
                p.drawRect(tr);
                // crack lines
                p.setPen(QPen(QColor("#78909C"), 1));
                p.drawLine(tr.topLeft()  + QPoint(4, 4),  tr.center());
                p.drawLine(tr.center(),  tr.bottomRight() - QPoint(4, 4));
                p.drawLine(tr.center(),  tr.center() + QPoint(-6,  6));
                p.drawLine(tr.center(),  tr.center() + QPoint( 6, -5));
                // red warning border
                p.setBrush(Qt::NoBrush);
                p.setPen(QPen(QColor(180, 30, 30, 180), 2));
                p.drawRect(tr);
            }
        }
    }

    // Snake head highlight and eyes
    auto [hx, hy] = m_controller->getHead();
    QRect hr = cellRect(hy, hx).adjusted(2, 2, -2, -2);
    p.setBrush(QBrush(snakeHead));
    p.setPen(QPen(Qt::black, 1));
    p.drawRoundedRect(hr, 5, 5);
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawEllipse(hr.x() + 5,  hr.y() + 5, 4, 4);
    p.drawEllipse(hr.x() + 14, hr.y() + 5, 4, 4);

    // grid lines
    p.setPen(QPen(gridLine, 1));
    int gw = m_cols * CELL_SIZE, gh = m_rows * CELL_SIZE;
    for (int x = 0; x <= m_cols; ++x)
        p.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, gh);
    for (int y = 0; y <= m_rows; ++y)
        p.drawLine(0, y * CELL_SIZE, gw, y * CELL_SIZE);

    //  border
    p.setPen(QPen(borderCol, 4));
    p.setBrush(Qt::NoBrush);
    p.drawRect(2, 2, gw - 4, gh - 4);

    // overlays
    if (m_paused && !m_dead) {
        p.fillRect(rect(), QColor(0, 0, 0, 130));
        QFont f; f.setPointSize(22); f.setBold(true);
        p.setFont(f);
        p.setPen(Qt::white);
        p.drawText(rect(), Qt::AlignCenter, "PAUSED\nPress P to resume");
    }
    if (m_dead) {
        p.fillRect(rect(), QColor(0, 0, 0, 160));
        QFont f; f.setPointSize(26); f.setBold(true);
        p.setFont(f);
        p.setPen(QColor("#FF5252"));
        p.drawText(rect(), Qt::AlignCenter,
                   QString("GAME OVER\nScore: %1").arg(m_controller->getScore()));
    }
}
