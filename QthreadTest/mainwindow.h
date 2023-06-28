#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
#include "mqtt/async_client.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "thread.h"

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
    mqtt::async_client client;
    Thread* mqtt_pub_t; // declare pub_thread
    Thread* mqtt_sub_t; // declare pub_thread
    Thread* cansend_t;
    Thread* candump_t;

private slots:
    void subscribe_btn();
};

#endif // MAINWINDOW_H