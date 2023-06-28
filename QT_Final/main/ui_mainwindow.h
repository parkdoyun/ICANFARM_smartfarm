/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *background_lbl;
    QLabel *upbar;
    QLabel *can_logo;
    QLabel *icanfarm_logo;
    QLabel *recent_logo;
    QLabel *setting_logo;
    QLabel *temp_img;
    QLabel *humid_img;
    QLabel *co2_img;
    QLabel *temp_recent_lbl;
    QLabel *temp_recent_lbl_2;
    QLabel *temp_recent_lbl_3;
    QLabel *temp_recent_lbl_4;
    QLabel *temp_recent_lbl_5;
    QLabel *temp_recent_lbl_6;
    QLabel *show_water;
    QLabel *show_sun;
    QLabel *show_co2;
    QLabel *show_wind;
    QLabel *pot_logo;
    QLabel *sun_logo;
    QLabel *cloud_logo;
    QLabel *wind_logo;
    QLabel *c_recent_logo;
    QLabel *percent_recent_logo;
    QLabel *ppm_recent_logo;
    QLabel *temp_text;
    QLabel *humid_text;
    QLabel *co2_text;
    QLabel *uptime_logo;
    QLabel *uptime_lbl;
    QLabel *h_logo;
    QLabel *ppm_setting_logo;
    QLabel *c_setting_logo;
    QLabel *percent_setting_logo;
    QPushButton *humid_down_btn;
    QPushButton *humid_up_btn;
    QPushButton *co2_up_btn;
    QPushButton *co2_down_btn;
    QPushButton *temperature_up_btn;
    QPushButton *temperature_down_btn;
    QLabel *temp_recent_text;
    QLabel *humid_recent_text;
    QLabel *co2_recent_text;
    QLabel *co2_setting_text;
    QLabel *humid_setting_text;
    QLabel *temp_setting_text;
    QLabel *uptime_text;
    QPushButton *logout_btn;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *change_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(800, 480));
        centralwidget->setMaximumSize(QSize(1280, 720));
        background_lbl = new QLabel(centralwidget);
        background_lbl->setObjectName(QString::fromUtf8("background_lbl"));
        background_lbl->setGeometry(QRect(0, 0, 1280, 720));
        background_lbl->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 51, 51);"));
        upbar = new QLabel(centralwidget);
        upbar->setObjectName(QString::fromUtf8("upbar"));
        upbar->setGeometry(QRect(0, 0, 1280, 72));
        upbar->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        can_logo = new QLabel(centralwidget);
        can_logo->setObjectName(QString::fromUtf8("can_logo"));
        can_logo->setGeometry(QRect(23, 8, 49, 55));
        sizePolicy.setHeightForWidth(can_logo->sizePolicy().hasHeightForWidth());
        can_logo->setSizePolicy(sizePolicy);
        can_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/can logo.png);"));
        icanfarm_logo = new QLabel(centralwidget);
        icanfarm_logo->setObjectName(QString::fromUtf8("icanfarm_logo"));
        icanfarm_logo->setGeometry(QRect(97, 21, 179, 30));
        icanfarm_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo icanfarm.png);"));
        recent_logo = new QLabel(centralwidget);
        recent_logo->setObjectName(QString::fromUtf8("recent_logo"));
        recent_logo->setGeometry(QRect(290, 110, 95, 29));
        recent_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo recent.png);\n"
"font: 40px;"));
        setting_logo = new QLabel(centralwidget);
        setting_logo->setObjectName(QString::fromUtf8("setting_logo"));
        setting_logo->setGeometry(QRect(560, 110, 95, 29));
        setting_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo setting.png);\n"
"font: 40px;"));
        temp_img = new QLabel(centralwidget);
        temp_img->setObjectName(QString::fromUtf8("temp_img"));
        temp_img->setGeometry(QRect(90, 170, 115, 106));
        sizePolicy.setHeightForWidth(temp_img->sizePolicy().hasHeightForWidth());
        temp_img->setSizePolicy(sizePolicy);
        temp_img->setStyleSheet(QString::fromUtf8("image: url(:/images/tabler_temperature.png);"));
        humid_img = new QLabel(centralwidget);
        humid_img->setObjectName(QString::fromUtf8("humid_img"));
        humid_img->setGeometry(QRect(100, 320, 88, 81));
        humid_img->setStyleSheet(QString::fromUtf8("image: url(:/images/ic_outline-water-drop.png);"));
        co2_img = new QLabel(centralwidget);
        co2_img->setObjectName(QString::fromUtf8("co2_img"));
        co2_img->setGeometry(QRect(110, 460, 88, 81));
        co2_img->setStyleSheet(QString::fromUtf8("image: url(:/images/mdi_periodic-table-carbon-dioxide.png);"));
        temp_recent_lbl = new QLabel(centralwidget);
        temp_recent_lbl->setObjectName(QString::fromUtf8("temp_recent_lbl"));
        temp_recent_lbl->setEnabled(true);
        temp_recent_lbl->setGeometry(QRect(220, 160, 237, 111));
        temp_recent_lbl->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        temp_recent_lbl_2 = new QLabel(centralwidget);
        temp_recent_lbl_2->setObjectName(QString::fromUtf8("temp_recent_lbl_2"));
        temp_recent_lbl_2->setEnabled(true);
        temp_recent_lbl_2->setGeometry(QRect(220, 300, 237, 111));
        temp_recent_lbl_2->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        temp_recent_lbl_3 = new QLabel(centralwidget);
        temp_recent_lbl_3->setObjectName(QString::fromUtf8("temp_recent_lbl_3"));
        temp_recent_lbl_3->setEnabled(true);
        temp_recent_lbl_3->setGeometry(QRect(220, 440, 237, 111));
        temp_recent_lbl_3->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        temp_recent_lbl_4 = new QLabel(centralwidget);
        temp_recent_lbl_4->setObjectName(QString::fromUtf8("temp_recent_lbl_4"));
        temp_recent_lbl_4->setEnabled(true);
        temp_recent_lbl_4->setGeometry(QRect(480, 160, 237, 111));
        temp_recent_lbl_4->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        temp_recent_lbl_5 = new QLabel(centralwidget);
        temp_recent_lbl_5->setObjectName(QString::fromUtf8("temp_recent_lbl_5"));
        temp_recent_lbl_5->setEnabled(true);
        temp_recent_lbl_5->setGeometry(QRect(480, 300, 237, 111));
        temp_recent_lbl_5->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        temp_recent_lbl_6 = new QLabel(centralwidget);
        temp_recent_lbl_6->setObjectName(QString::fromUtf8("temp_recent_lbl_6"));
        temp_recent_lbl_6->setEnabled(true);
        temp_recent_lbl_6->setGeometry(QRect(480, 440, 237, 111));
        temp_recent_lbl_6->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        show_water = new QLabel(centralwidget);
        show_water->setObjectName(QString::fromUtf8("show_water"));
        show_water->setGeometry(QRect(890, 210, 150, 150));
        show_water->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        show_sun = new QLabel(centralwidget);
        show_sun->setObjectName(QString::fromUtf8("show_sun"));
        show_sun->setGeometry(QRect(1060, 210, 150, 150));
        show_sun->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        show_co2 = new QLabel(centralwidget);
        show_co2->setObjectName(QString::fromUtf8("show_co2"));
        show_co2->setGeometry(QRect(890, 380, 150, 150));
        show_co2->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        show_wind = new QLabel(centralwidget);
        show_wind->setObjectName(QString::fromUtf8("show_wind"));
        show_wind->setGeometry(QRect(1060, 380, 150, 150));
        show_wind->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        pot_logo = new QLabel(centralwidget);
        pot_logo->setObjectName(QString::fromUtf8("pot_logo"));
        pot_logo->setGeometry(QRect(940, 260, 70, 55));
        pot_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/tabler_temperature.png);\n"
"image: url(:/images/logo_pot.png);"));
        sun_logo = new QLabel(centralwidget);
        sun_logo->setObjectName(QString::fromUtf8("sun_logo"));
        sun_logo->setGeometry(QRect(1110, 260, 55, 55));
        sun_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_sun.png);"));
        cloud_logo = new QLabel(centralwidget);
        cloud_logo->setObjectName(QString::fromUtf8("cloud_logo"));
        cloud_logo->setGeometry(QRect(940, 430, 55, 55));
        cloud_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_cloud.png);"));
        wind_logo = new QLabel(centralwidget);
        wind_logo->setObjectName(QString::fromUtf8("wind_logo"));
        wind_logo->setGeometry(QRect(1110, 430, 55, 55));
        wind_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_wind.png);"));
        c_recent_logo = new QLabel(centralwidget);
        c_recent_logo->setObjectName(QString::fromUtf8("c_recent_logo"));
        c_recent_logo->setGeometry(QRect(370, 190, 45, 45));
        c_recent_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_c.png);"));
        percent_recent_logo = new QLabel(centralwidget);
        percent_recent_logo->setObjectName(QString::fromUtf8("percent_recent_logo"));
        percent_recent_logo->setGeometry(QRect(370, 330, 45, 45));
        percent_recent_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_percent.png);"));
        ppm_recent_logo = new QLabel(centralwidget);
        ppm_recent_logo->setObjectName(QString::fromUtf8("ppm_recent_logo"));
        ppm_recent_logo->setGeometry(QRect(370, 490, 45, 24));
        ppm_recent_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_ppm.png);"));
        temp_text = new QLabel(centralwidget);
        temp_text->setObjectName(QString::fromUtf8("temp_text"));
        temp_text->setGeometry(QRect(500, 180, 141, 71));
        temp_text->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        humid_text = new QLabel(centralwidget);
        humid_text->setObjectName(QString::fromUtf8("humid_text"));
        humid_text->setGeometry(QRect(500, 320, 140, 71));
        humid_text->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        co2_text = new QLabel(centralwidget);
        co2_text->setObjectName(QString::fromUtf8("co2_text"));
        co2_text->setGeometry(QRect(500, 460, 141, 71));
        co2_text->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        uptime_logo = new QLabel(centralwidget);
        uptime_logo->setObjectName(QString::fromUtf8("uptime_logo"));
        uptime_logo->setGeometry(QRect(940, 600, 87, 36));
        uptime_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo uptime.png);"));
        uptime_lbl = new QLabel(centralwidget);
        uptime_lbl->setObjectName(QString::fromUtf8("uptime_lbl"));
        uptime_lbl->setGeometry(QRect(1045, 589, 171, 51));
        uptime_lbl->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 91, 101);"));
        h_logo = new QLabel(centralwidget);
        h_logo->setObjectName(QString::fromUtf8("h_logo"));
        h_logo->setGeometry(QRect(1175, 599, 31, 31));
        h_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/h.png);"));
        ppm_setting_logo = new QLabel(centralwidget);
        ppm_setting_logo->setObjectName(QString::fromUtf8("ppm_setting_logo"));
        ppm_setting_logo->setGeometry(QRect(650, 490, 45, 24));
        ppm_setting_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_ppm.png);"));
        c_setting_logo = new QLabel(centralwidget);
        c_setting_logo->setObjectName(QString::fromUtf8("c_setting_logo"));
        c_setting_logo->setGeometry(QRect(650, 190, 45, 45));
        c_setting_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_c.png);"));
        percent_setting_logo = new QLabel(centralwidget);
        percent_setting_logo->setObjectName(QString::fromUtf8("percent_setting_logo"));
        percent_setting_logo->setGeometry(QRect(650, 330, 45, 45));
        percent_setting_logo->setStyleSheet(QString::fromUtf8("image: url(:/images/logo_percent.png);"));
        humid_down_btn = new QPushButton(centralwidget);
        humid_down_btn->setObjectName(QString::fromUtf8("humid_down_btn"));
        humid_down_btn->setGeometry(QRect(730, 360, 51, 51));
        humid_down_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_down.png);\n"
"border:0px;"));
        humid_up_btn = new QPushButton(centralwidget);
        humid_up_btn->setObjectName(QString::fromUtf8("humid_up_btn"));
        humid_up_btn->setGeometry(QRect(730, 300, 51, 51));
        humid_up_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_up.png);\n"
"border:0px;"));
        co2_up_btn = new QPushButton(centralwidget);
        co2_up_btn->setObjectName(QString::fromUtf8("co2_up_btn"));
        co2_up_btn->setGeometry(QRect(730, 440, 51, 51));
        co2_up_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_up.png);\n"
"border:0px;"));
        co2_down_btn = new QPushButton(centralwidget);
        co2_down_btn->setObjectName(QString::fromUtf8("co2_down_btn"));
        co2_down_btn->setGeometry(QRect(730, 500, 51, 51));
        co2_down_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_down.png);\n"
"border:0px;"));
        temperature_up_btn = new QPushButton(centralwidget);
        temperature_up_btn->setObjectName(QString::fromUtf8("temperature_up_btn"));
        temperature_up_btn->setGeometry(QRect(730, 160, 51, 51));
        temperature_up_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_up.png);\n"
"border:0px;"));
        temperature_down_btn = new QPushButton(centralwidget);
        temperature_down_btn->setObjectName(QString::fromUtf8("temperature_down_btn"));
        temperature_down_btn->setGeometry(QRect(730, 220, 51, 51));
        temperature_down_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"image: url(:/images/arrow_down.png);\n"
"border:0px;"));
        temp_recent_text = new QLabel(centralwidget);
        temp_recent_text->setObjectName(QString::fromUtf8("temp_recent_text"));
        temp_recent_text->setGeometry(QRect(270, 180, 91, 61));
        temp_recent_text->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 45px;"));
        humid_recent_text = new QLabel(centralwidget);
        humid_recent_text->setObjectName(QString::fromUtf8("humid_recent_text"));
        humid_recent_text->setGeometry(QRect(270, 330, 101, 40));
        humid_recent_text->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 45px;"));
        co2_recent_text = new QLabel(centralwidget);
        co2_recent_text->setObjectName(QString::fromUtf8("co2_recent_text"));
        co2_recent_text->setGeometry(QRect(270, 480, 91, 40));
        co2_recent_text->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 45px;"));
        co2_setting_text = new QLabel(centralwidget);
        co2_setting_text->setObjectName(QString::fromUtf8("co2_setting_text"));
        co2_setting_text->setGeometry(QRect(512, 476, 101, 40));
        co2_setting_text->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 45px;"));
        humid_setting_text = new QLabel(centralwidget);
        humid_setting_text->setObjectName(QString::fromUtf8("humid_setting_text"));
        humid_setting_text->setGeometry(QRect(510, 330, 111, 40));
        humid_setting_text->setStyleSheet(QString::fromUtf8("color: rgb(0,0,0);\n"
"font: 45px;"));
        temp_setting_text = new QLabel(centralwidget);
        temp_setting_text->setObjectName(QString::fromUtf8("temp_setting_text"));
        temp_setting_text->setGeometry(QRect(510, 190, 111, 40));
        temp_setting_text->setStyleSheet(QString::fromUtf8("color: rgb(0,0,0);\n"
"font: 45px;"));
        uptime_text = new QLabel(centralwidget);
        uptime_text->setObjectName(QString::fromUtf8("uptime_text"));
        uptime_text->setGeometry(QRect(1100, 590, 71, 40));
        uptime_text->setStyleSheet(QString::fromUtf8("color: rgb(255,255,255);\n"
"font: 36px;"));
        logout_btn = new QPushButton(centralwidget);
        logout_btn->setObjectName(QString::fromUtf8("logout_btn"));
        logout_btn->setGeometry(QRect(1130, 20, 120, 30));
        logout_btn->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"image: url(:/images/logo logout.png);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(890, 90, 51, 51));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(940, 90, 51, 51));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(990, 90, 51, 51));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(1040, 90, 51, 51));
        change_btn = new QPushButton(centralwidget);
        change_btn->setObjectName(QString::fromUtf8("change_btn"));
        change_btn->setGeometry(QRect(480, 580, 301, 62));
        change_btn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(61, 91, 101, 255));\n"
"border: 0px;\n"
"color: rgb(255, 255, 255);\n"
"font: 40px;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 1280, 26));
        menubar->setNativeMenuBar(true);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(false);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(humid_up_btn, SIGNAL(clicked()), MainWindow, SLOT(upHumid()));
        QObject::connect(humid_down_btn, SIGNAL(clicked()), MainWindow, SLOT(downHumid()));
        QObject::connect(co2_down_btn, SIGNAL(clicked()), MainWindow, SLOT(downCo2()));
        QObject::connect(co2_up_btn, SIGNAL(clicked()), MainWindow, SLOT(upCo2()));
        QObject::connect(temperature_down_btn, SIGNAL(clicked()), MainWindow, SLOT(downTemperature()));
        QObject::connect(temperature_up_btn, SIGNAL(clicked()), MainWindow, SLOT(upTemperature()));
        QObject::connect(logout_btn, SIGNAL(clicked()), MainWindow, SLOT(goLogout()));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(changeWaterColor()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(changeSunColor()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), MainWindow, SLOT(changeWindColor()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), MainWindow, SLOT(changeCloudColor()));
        QObject::connect(change_btn, SIGNAL(clicked()), MainWindow, SLOT(changeValue()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        background_lbl->setText(QString());
        upbar->setText(QString());
        can_logo->setText(QString());
        icanfarm_logo->setText(QString());
        recent_logo->setText(QString());
        setting_logo->setText(QString());
        temp_img->setText(QString());
        humid_img->setText(QString());
        co2_img->setText(QString());
        temp_recent_lbl->setText(QString());
        temp_recent_lbl_2->setText(QString());
        temp_recent_lbl_3->setText(QString());
        temp_recent_lbl_4->setText(QString());
        temp_recent_lbl_5->setText(QString());
        temp_recent_lbl_6->setText(QString());
        show_water->setText(QString());
        show_sun->setText(QString());
        show_co2->setText(QString());
        show_wind->setText(QString());
        pot_logo->setText(QString());
        sun_logo->setText(QString());
        cloud_logo->setText(QString());
        wind_logo->setText(QString());
        c_recent_logo->setText(QString());
        percent_recent_logo->setText(QString());
        ppm_recent_logo->setText(QString());
        temp_text->setText(QString());
        humid_text->setText(QString());
        co2_text->setText(QString());
        uptime_logo->setText(QString());
        uptime_lbl->setText(QString());
        h_logo->setText(QString());
        ppm_setting_logo->setText(QString());
        c_setting_logo->setText(QString());
        percent_setting_logo->setText(QString());
        humid_down_btn->setText(QString());
        humid_up_btn->setText(QString());
        co2_up_btn->setText(QString());
        co2_down_btn->setText(QString());
        temperature_up_btn->setText(QString());
        temperature_down_btn->setText(QString());
        temp_recent_text->setText(QCoreApplication::translate("MainWindow", "28.2", nullptr));
        humid_recent_text->setText(QCoreApplication::translate("MainWindow", "67.8", nullptr));
        co2_recent_text->setText(QCoreApplication::translate("MainWindow", "400", nullptr));
        co2_setting_text->setText(QCoreApplication::translate("MainWindow", "400", nullptr));
        humid_setting_text->setText(QCoreApplication::translate("MainWindow", "64.0", nullptr));
        temp_setting_text->setText(QCoreApplication::translate("MainWindow", "30.0", nullptr));
        uptime_text->setText(QCoreApplication::translate("MainWindow", "92", nullptr));
        logout_btn->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "water", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "sun", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "wind", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "cloud", nullptr));
        change_btn->setText(QCoreApplication::translate("MainWindow", "\353\263\200\352\262\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
