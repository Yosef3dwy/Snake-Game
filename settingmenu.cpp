#include "settingmenu.h"
#include "mainwindow.h"
#include "ui_settingmenu.h"
#include <QButtonGroup>

SettingMenu::SettingMenu(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingMenu)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: #EDC9AF; }");

    // Difficulty group
    ui->Easy->setCheckable(true);
    ui->Medium->setCheckable(true);
    ui->Hard->setCheckable(true);
    QButtonGroup *group1 = new QButtonGroup(this);
    group1->addButton(ui->Easy);
    group1->addButton(ui->Medium);
    group1->addButton(ui->Hard);
    group1->setExclusive(true);
    ui->Medium->setChecked(true);   // sensible default

    // Grid size group
    ui->S15X15->setCheckable(true);
    ui->S20X20->setCheckable(true);
    ui->S25X25->setCheckable(true);
    QButtonGroup *group2 = new QButtonGroup(this);
    group2->addButton(ui->S15X15);
    group2->addButton(ui->S20X20);
    group2->addButton(ui->S25X25);
    group2->setExclusive(true);
    ui->S20X20->setChecked(true);   // sensible default

    // Volume slider range
    ui->MainVolSilder->setRange(0, 100);
    ui->MainVolSilder->setValue(50);

    connect(ui->MainVolSilder, &QSlider::valueChanged,
            this, &SettingMenu::volumeChanged);
}

SettingMenu::~SettingMenu()
{
    delete ui;
}

void SettingMenu::on_Back_clicked()
{
    emit backClicked();
}

void SettingMenu::setInitialVolume(int value)
{
    ui->MainVolSilder->blockSignals(true);
    ui->MainVolSilder->setValue(value);
    ui->MainVolSilder->blockSignals(false);
}

bool SettingMenu::isS15Selected() const { return ui->S15X15->isChecked(); }
bool SettingMenu::isS20Selected() const { return ui->S20X20->isChecked(); }
bool SettingMenu::isS25Selected() const { return ui->S25X25->isChecked(); }

int SettingMenu::getDifficulty() const
{
    if (ui->Easy->isChecked())   return 1;
    if (ui->Hard->isChecked())   return 3;
    return 2; // Medium default
}