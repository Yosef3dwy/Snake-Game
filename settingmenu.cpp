#include "settingmenu.h"
#include "mainwindow.h"
#include "ui_settingmenu.h"
#include <QButtonGroup>

SettingMenu::SettingMenu(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingMenu)
{
    ui->setupUi(this);
    setStyleSheet("QWidget { background-color: #EDC9AF; }");

    ui->Easy->setCheckable(true);
    ui->Medium->setCheckable(true);
    ui->Hard->setCheckable(true);
    QButtonGroup *g1 = new QButtonGroup(this);
    g1->addButton(ui->Easy);
    g1->addButton(ui->Medium);
    g1->addButton(ui->Hard);
    g1->setExclusive(true);
    ui->Medium->setChecked(true);

    ui->S15X15->setCheckable(true);
    ui->S20X20->setCheckable(true);
    ui->S25X25->setCheckable(true);
    QButtonGroup *g2 = new QButtonGroup(this);
    g2->addButton(ui->S15X15);
    g2->addButton(ui->S20X20);
    g2->addButton(ui->S25X25);
    g2->setExclusive(true);
    ui->S20X20->setChecked(true);

    ui->MainVolSilder->setRange(0, 100);
    ui->MainVolSilder->setValue(50);

    connect(ui->MainVolSilder, &QSlider::valueChanged,
            this, &SettingMenu::volumeChanged);
}

SettingMenu::~SettingMenu() { delete ui; }

void SettingMenu::on_Back_clicked() { emit backClicked(); }

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
    if (ui->Easy->isChecked()) return 1;
    if (ui->Hard->isChecked()) return 3;
    return 2;
}