#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QTimer>
#include <QKeyEvent>
#include <QSoundEffect>
#include "gamecontroller.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr int CELL_SIZE = 30; // must be computed in compile time and be const

    GameWidget(int rows, int cols, int difficulty, int volume, bool dropTiles, QWidget *parent = nullptr);

    void setEatVolume(int value);

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

    QSoundEffect    *m_eatSound;
};

#endif // GAMEWIDGET_H
