#include "mainwindow.h"
#include "settingmenu.h"
#include "start.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDir>
#include <QUrl>
#include <QApplication>
#include <QDebug>


static QSoundEffect *bgMusic = new QSoundEffect;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString base = QDir::currentPath();

    // Background image
    QPixmap pix(base + "/BG.png");
    ui->label->setPixmap(pix);
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0, 0, width(), height());
    ui->label->lower();
    ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    bgMusic->setSource(QUrl::fromLocalFile(base + "/BG_music.wav"));
    bgMusic->setVolume(0.5f);
    bgMusic->setLoopCount(QSoundEffect::Infinite);

    connect(bgMusic, &QSoundEffect::statusChanged, this, [=]() {
        qDebug() << "BGMusic status:" << bgMusic->status()
        << "| source:" << bgMusic->source();
    });

    bgMusic->play();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Start_clicked()
{
    int rows = 20, cols = 20, difficulty = 2, volume = 80;
    bool dropTiles = false;

    if (settingmenu) {
        if      (settingmenu->isS15Selected()) { rows = 15; cols = 15; }
        else if (settingmenu->isS25Selected()) { rows = 25; cols = 25; }
        else                                   { rows = 20; cols = 20; }

        difficulty = settingmenu->getDifficulty();
        volume     = settingmenu->getSFXVolume();
        dropTiles  = settingmenu->isDropTilesEnabled();
    }

    start *s = new start(rows, cols, difficulty, volume, dropTiles);
    this->hide();
    s->show();
}

void MainWindow::on_Settings_clicked()
{
    if (!settingmenu) {
        settingmenu = new SettingMenu(nullptr);
        settingmenu->setWindowFlags(Qt::Window);

        connect(settingmenu, &SettingMenu::volumeChanged, this, [=](int v) {
            bgMusic->setVolume(v / 100.0f);
        });

        connect(settingmenu, &SettingMenu::backClicked, this, [=]() {
            settingmenu->hide();
            this->show();
            this->raise();
            this->activateWindow();
        });
    }

    settingmenu->setInitialVolume(static_cast<int>(bgMusic->volume() * 100));
    this->hide();
    settingmenu->show();
}

void MainWindow::on_Exit_clicked()
{
    QApplication::quit();
}