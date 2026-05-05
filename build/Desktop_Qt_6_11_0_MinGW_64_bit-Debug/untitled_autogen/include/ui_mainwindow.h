/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Start;
    QPushButton *Exit;
    QPushButton *Settings;
    QLabel *label;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 760);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Start = new QPushButton(centralwidget);
        Start->setObjectName("Start");
        Start->setGeometry(QRect(570, 360, 221, 51));
        Start->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4CAF50;\n"
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
"}"));
        Exit = new QPushButton(centralwidget);
        Exit->setObjectName("Exit");
        Exit->setGeometry(QRect(570, 520, 221, 51));
        Exit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e53935;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ef5350;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #c62828;\n"
"}"));
        Settings = new QPushButton(centralwidget);
        Settings->setObjectName("Settings");
        Settings->setGeometry(QRect(570, 440, 221, 51));
        Settings->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2b2b2b;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #404040;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1400, 680));
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        MainWindow->setCentralWidget(centralwidget);
        label->raise();
        Start->raise();
        Exit->raise();
        Settings->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1400, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(Settings, &QPushButton::clicked, Settings, qOverload<>(&QPushButton::showMenu));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        Exit->setText(QCoreApplication::translate("MainWindow", "Exit ", nullptr));
        Settings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
