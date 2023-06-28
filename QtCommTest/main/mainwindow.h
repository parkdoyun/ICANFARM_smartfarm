#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_mainwindow.h"
#include "thread.h"
#include "mqtt.h"
#include "login_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    login_dialog* login_D; // login dialog
    mqtt::async_client mqtt_client;
    QSerialPort* serial_port;
    Thread* recvMqttFromServer_t;
    Thread* tempSensorProcess_t;

private slots:
    void upTemperature();
    void downTemperature();
    void downHumid();
    void upHumid();
    void upCo2();
    void downCo2();
    void goLogout();
    void changeWaterColor();
    void changeWindColor();
    void changeSunColor();
    void changeCloudColor();
    void changeValue();
    void recvLogInResult(int flag); // 로그인 결과에 따라 login_diglog로부터 값 수신
    void sendMqtt2Server(const std::string topic, const std::string msg); // 서버로 MQTT 전송
    void applyServerTemp(double t); // mqtt.h에서 보내는 signal과 연결
    void applyServerHumid(double h); // mqtt.h에서 보내는 signal과 연결
    void applyServerCo2(int co); // mqtt.h에서 보내는 signal과 연결
    void updateTempData(double t);
    void updateHumidData(double h);
    void updateCo2Data(int co);
};

#endif // MAINWINDOW_H
