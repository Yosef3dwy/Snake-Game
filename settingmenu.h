#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QWidget>

namespace Ui {
class SettingMenu;
}

class SettingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SettingMenu(QWidget *parent = nullptr);
    ~SettingMenu();

private slots:
    void on_Back_clicked();

private:
    Ui::SettingMenu *ui;
};

#endif // SETTINGMENU_H
