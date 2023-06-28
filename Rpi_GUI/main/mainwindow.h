
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>

#include "login_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    login_dialog *login_D; // login dialog

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
    void receiveSensorValue(int flag); // 로그인 결과에 따라 login_diglog로부터 값 수신
};

#endif // MAINWINDOW_H
