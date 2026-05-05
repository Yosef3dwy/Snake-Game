#include "mainwindow.h"
#include "settingmenu.h"
#include "start.h"
#include "./ui_mainwindow.h"
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Owner/Desktop/DSA_Project/untitled/BG.png");

    ui->label->setPixmap(pix);
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0, 0, width(), height());
    ui->label->lower();                   // push behind all other widgets
    ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true); // FIX: let clicks pass through
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Start_clicked()
{
    start *startmenu = new start();

    this->hide();

    startmenu->show();
}


void MainWindow::on_Settings_clicked()
{
    SettingMenu *settingmenu = new SettingMenu();

    settingmenu->show();
    this->hide();


}


void MainWindow::on_Exit_clicked()
{
    QApplication::quit();
}