#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QWidget>

namespace Ui { class SettingMenu; }

class SettingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SettingMenu(QWidget *parent = nullptr);
    void setInitialVolume(int value);
    ~SettingMenu();

    bool isS15Selected() const;
    bool isS20Selected() const;
    bool isS25Selected() const;
    int  getDifficulty() const;   // 1=Easy 2=Medium 3=Hard
    int getCurrentVolume() const;

signals:
    void volumeChanged(int value);
    void backClicked();

private slots:
    void on_Back_clicked();

private:
    Ui::SettingMenu *ui;
};

#endif // SETTINGMENU_H