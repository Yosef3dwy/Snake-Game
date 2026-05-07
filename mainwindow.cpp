#include "mainwindow.h"
#include "settingmenu.h"
#include "start.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

QMediaPlayer *player = new QMediaPlayer;
QAudioOutput *audio  = new QAudioOutput;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString base = QCoreApplication::applicationDirPath();

    QPixmap pix(base + "/BG.png");
    ui->label->setPixmap(pix);
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0, 0, width(), height());
    ui->label->lower();
    ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    player->setAudioOutput(audio);
    player->setSource(QUrl::fromLocalFile(base + "/BG_music.mp3"));
    audio->setVolume(0.5f);
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Start_clicked()
{
    int rows = 20, cols = 20, difficulty = 2;
    int volume = 50; // default
    if (settingmenu) {
        if      (settingmenu->isS15Selected()) { rows = 15; cols = 15; }
        else if (settingmenu->isS25Selected()) { rows = 25; cols = 25; }
        difficulty = settingmenu->getDifficulty();
        volume = settingmenu->getCurrentVolume();
    }
    start *s = new start(rows, cols, difficulty, volume);
    this->hide();
    s->show();
}

void MainWindow::on_Settings_clicked()
{
    if (!settingmenu) {
        settingmenu = new SettingMenu(nullptr);
        settingmenu->setWindowFlags(Qt::Window);

        connect(settingmenu, &SettingMenu::volumeChanged, this, [=](int v){
            audio->setVolume(v / 100.0f);
        });
        connect(settingmenu, &SettingMenu::backClicked, this, [=](){
            settingmenu->hide();
            this->show(); this->raise(); this->activateWindow();
        });

    }

    settingmenu->setInitialVolume(static_cast<int>(audio->volume() * 100));
    this->hide();
    settingmenu->show();
}

void MainWindow::on_Exit_clicked()
{
    QApplication::quit();
}