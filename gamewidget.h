#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QTimer>
#include <QKeyEvent>
#include "enums.h"
#include "board.h"
#include "snake.h"
#include "gamecontroller.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    // PUBLIC so start.cpp can compute gridW/gridH
    static constexpr int CELL_SIZE = 30;

    explicit GameWidget(int rows, int cols, int difficulty, QWidget *parent = nullptr);

    QPoint cellPos(int row, int col) const;
    QRect  cellRect(int row, int col) const;

    int rows() const { return m_rows; }
    int cols() const { return m_cols; }

signals:
    void gameOver(int score);
    void scoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onTick();

private:
    int              m_rows;
    int              m_cols;
    GameController  *m_controller;
    QTimer          *m_timer;
    bool             m_paused;
    bool             m_dead;
};

#endif // GAMEWIDGET_H