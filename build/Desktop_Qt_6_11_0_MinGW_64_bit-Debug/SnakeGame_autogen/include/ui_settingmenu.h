/********************************************************************************
** Form generated from reading UI file 'settingmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMENU_H
#define UI_SETTINGMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingMenu
{
public:
    QPushButton *Easy;
    QPushButton *Medium;
    QPushButton *Hard;
    QLabel *Difficulty;
    QLabel *GridSize;
    QPushButton *S15X15;
    QPushButton *S20X20;
    QPushButton *S25X25;
    QSlider *SFXSlider;
    QLabel *SFX;
    QLabel *MainVol;
    QSlider *MainVolSilder;
    QPushButton *Back;
    QCheckBox *checkBox;

    void setupUi(QWidget *SettingMenu)
    {
        if (SettingMenu->objectName().isEmpty())
            SettingMenu->setObjectName("SettingMenu");
        SettingMenu->resize(1400, 760);
        Easy = new QPushButton(SettingMenu);
        Easy->setObjectName("Easy");
        Easy->setGeometry(QRect(170, 250, 231, 71));
        Easy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        Medium = new QPushButton(SettingMenu);
        Medium->setObjectName("Medium");
        Medium->setGeometry(QRect(170, 360, 231, 71));
        Medium->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        Hard = new QPushButton(SettingMenu);
        Hard->setObjectName("Hard");
        Hard->setGeometry(QRect(170, 470, 231, 71));
        Hard->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        Difficulty = new QLabel(SettingMenu);
        Difficulty->setObjectName("Difficulty");
        Difficulty->setGeometry(QRect(200, 100, 181, 61));
        Difficulty->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /* Black background */\n"
"    background-color: #000000;\n"
"\n"
"    /* White text */\n"
"    color: #ffffff;\n"
"\n"
"    /* Styling */\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"\n"
"    /* \360\237\224\245 Font size added */\n"
"    font-size: 20px;\n"
"}\n"
"\n"
"/* Hover effect */\n"
"QLabel:hover {\n"
"    background-color: #333333;\n"
"}"));
        GridSize = new QLabel(SettingMenu);
        GridSize->setObjectName("GridSize");
        GridSize->setGeometry(QRect(540, 100, 181, 61));
        GridSize->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /* Black background */\n"
"    background-color: #000000;\n"
"\n"
"    /* White text */\n"
"    color: #ffffff;\n"
"\n"
"    /* Styling */\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"\n"
"    /* \360\237\224\245 Font size added */\n"
"    font-size: 20px;\n"
"}\n"
"\n"
"/* Hover effect */\n"
"QLabel:hover {\n"
"    background-color: #333333;\n"
"}"));
        S15X15 = new QPushButton(SettingMenu);
        S15X15->setObjectName("S15X15");
        S15X15->setGeometry(QRect(510, 250, 231, 71));
        S15X15->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        S20X20 = new QPushButton(SettingMenu);
        S20X20->setObjectName("S20X20");
        S20X20->setGeometry(QRect(510, 360, 231, 71));
        S20X20->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        S25X25 = new QPushButton(SettingMenu);
        S25X25->setObjectName("S25X25");
        S25X25->setGeometry(QRect(510, 470, 231, 71));
        S25X25->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0a0aa1;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66bb6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #388E3C;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #4CAF50;\n"
"}"));
        SFXSlider = new QSlider(SettingMenu);
        SFXSlider->setObjectName("SFXSlider");
        SFXSlider->setGeometry(QRect(990, 280, 160, 18));
        SFXSlider->setOrientation(Qt::Orientation::Horizontal);
        SFX = new QLabel(SettingMenu);
        SFX->setObjectName("SFX");
        SFX->setGeometry(QRect(880, 270, 61, 41));
        SFX->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /* Black background as requested */\n"
"    background-color: #EDC9AF;\n"
"    \n"
"    /* White text to contrast with black */\n"
"    color: #ffffff;\n"
"    \n"
"    /* Keeping your previous styling preferences */\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        MainVol = new QLabel(SettingMenu);
        MainVol->setObjectName("MainVol");
        MainVol->setGeometry(QRect(840, 390, 131, 41));
        MainVol->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /* Black background as requested */\n"
"    background-color: #EDC9AF;\n"
"    \n"
"    /* White text to contrast with black */\n"
"    color: #ffffff;\n"
"    \n"
"    /* Keeping your previous styling preferences */\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        MainVolSilder = new QSlider(SettingMenu);
        MainVolSilder->setObjectName("MainVolSilder");
        MainVolSilder->setGeometry(QRect(990, 400, 160, 18));
        MainVolSilder->setOrientation(Qt::Orientation::Horizontal);
        Back = new QPushButton(SettingMenu);
        Back->setObjectName("Back");
        Back->setGeometry(QRect(1030, 110, 90, 29));
        Back->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ff5c5c;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #c0392b;\n"
"}"));
        checkBox = new QCheckBox(SettingMenu);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(990, 510, 131, 25));
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    color: red;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 28px;\n"
"    height: 28px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"    background-color: #444;\n"
"    border: 2px solid #888;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #2ecc71;\n"
"    border: 2px solid #27ae60;\n"
"}\n"
"\n"
"QCheckBox::indicator:hover {\n"
"    border: 2px solid #00bcd4;\n"
"}"));

        retranslateUi(SettingMenu);
        QObject::connect(Back, &QPushButton::clicked, Back, qOverload<>(&QPushButton::showMenu));

        QMetaObject::connectSlotsByName(SettingMenu);
    } // setupUi

    void retranslateUi(QWidget *SettingMenu)
    {
        SettingMenu->setWindowTitle(QCoreApplication::translate("SettingMenu", "Form", nullptr));
        Easy->setText(QCoreApplication::translate("SettingMenu", "Easy", nullptr));
        Medium->setText(QCoreApplication::translate("SettingMenu", "Medium", nullptr));
        Hard->setText(QCoreApplication::translate("SettingMenu", "Hard", nullptr));
        Difficulty->setText(QCoreApplication::translate("SettingMenu", "Difficulty ", nullptr));
        GridSize->setText(QCoreApplication::translate("SettingMenu", "Grid Size", nullptr));
        S15X15->setText(QCoreApplication::translate("SettingMenu", "15 X 15", nullptr));
        S20X20->setText(QCoreApplication::translate("SettingMenu", "20 X 20", nullptr));
        S25X25->setText(QCoreApplication::translate("SettingMenu", "25 X 25", nullptr));
        SFX->setText(QCoreApplication::translate("SettingMenu", "SFX", nullptr));
        MainVol->setText(QCoreApplication::translate("SettingMenu", "main volume", nullptr));
        Back->setText(QCoreApplication::translate("SettingMenu", "Back", nullptr));
        checkBox->setText(QCoreApplication::translate("SettingMenu", "Drop Tiles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMenu: public Ui_SettingMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMENU_H
