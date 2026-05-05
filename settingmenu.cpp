#include "settingmenu.h"
#include "mainwindow.h"
#include "ui_settingmenu.h"
#include <QButtonGroup>

SettingMenu::SettingMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingMenu)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: #EDC9AF; }");

    ui->Easy->setCheckable(true);
    ui->Medium->setCheckable(true);
    ui->Hard->setCheckable(true);
    QButtonGroup *group1 = new QButtonGroup(this);
    group1->addButton(ui->Easy);
    group1->addButton(ui->Medium);
    group1->addButton(ui->Hard);
    group1->setExclusive(true);



    ui->S15X15->setCheckable(true);
    ui->S20X20->setCheckable(true);
    ui->S25X25->setCheckable(true);
    QButtonGroup *group2 = new QButtonGroup(this);
    group2->addButton(ui->S15X15);
    group2->addButton(ui->S20X20);
    group2->addButton(ui->S25X25);
    group2->setExclusive(true);




}

SettingMenu::~SettingMenu()
{
    delete ui;
}


void SettingMenu::on_Back_clicked()
{
    MainWindow  *mainmenu = new MainWindow();
    this->hide();
    mainmenu->show();
}

