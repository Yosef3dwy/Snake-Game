#ifndef START_H
#define START_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "gamewidget.h"

namespace Ui { class start; }

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(int rows, int cols, int difficulty, QWidget *parent = nullptr);
    ~start();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onScoreChanged(int score);
    void onGameOver(int score);
    void onRestart();
    void onBackToMenu();

private:
    Ui::start  *ui;
    GameWidget *game;
    QLabel     *scoreLabel;
    QLabel     *gameOverLabel;
    QPushButton *restartBtn;
    QPushButton *menuBtn;

    int m_rows;
    int m_cols;
    int m_difficulty;

    void buildUI();
    void launchGame();
};

#endif // START_H