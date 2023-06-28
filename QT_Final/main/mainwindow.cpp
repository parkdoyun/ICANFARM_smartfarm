#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
#include <string>

// Create MQTT client instance
const std::string MQTT_SERVER_ADDRESS = "tcp://k8a206.p.ssafy.io:3333";
const std::string CLIENT_ID = "1";
mqtt::async_client mqtt_client(MQTT_SERVER_ADDRESS, CLIENT_ID);
MqttCallback cb;
mqtt::connect_options connOpts;

// Mainwindow 생성자
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mqtt_client(MQTT_SERVER_ADDRESS, CLIENT_ID)
{
    ui->setupUi(this);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);

    ui->show_water->setStyleSheet("background-color: rgb(255, 255, 0);");
    ui->show_wind->setStyleSheet("background-color: rgb(255, 255, 0);");
    ui->show_sun->setStyleSheet("background-color: rgb(255, 255, 0);");

    // Set up MQTT client options
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    mqtt_client.set_callback(cb);
    connOpts.set_clean_session(true);

    std::cout << "Connecting to the MQTT server..." << std::endl;
    try
    {
        mqtt::token_ptr conntok = mqtt_client.connect(connOpts);
        conntok->wait();
        std::cout << "Connected." << std::endl;
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    // 시리얼 포트 연결 
    temp_port = new QSerialPort();
    temp_port->setPortName("/dev/ttyACM1");
    temp_port->setBaudRate(QSerialPort::Baud115200);
    ///*temp_port->setDataBits(QSerialPort::Data8);
    //temp_port->setParity(QSerialPort::NoParity);
    //temp_port->setStopBits(QSerialPort::OneStop);
    //temp_port->setFlowControl(QSerialPort::NoFlowControl);*/

    //// 버퍼 크기 설정
    ////temp_port->setReadBufferSize(8192);

    if (temp_port->open(QIODevice::ReadWrite))
    {
        // Serial port is opened and ready for communication
        std::cout << "TEMP serial port is opened." << std::endl;
    }
    else
    {
        // Failed to open serial port
        std::cerr << "Failed to open TEMP serial port." << std::endl;
    }

    humid_port = new QSerialPort();
    humid_port->setPortName("/dev/ttyACM0");
    humid_port->setBaudRate(QSerialPort::Baud115200);
    if (humid_port->open(QIODevice::ReadWrite))
    {
        std::cout << "HUMID serial port is opened." << std::endl;
    }
    else
    {
        std::cerr << "Failed to open HUMID serial port." << std::endl;
    }

    co2_port = new QSerialPort();
    co2_port->setPortName("/dev/ttyACM2");
    co2_port->setBaudRate(QSerialPort::Baud115200);
    if (co2_port->open(QIODevice::ReadWrite))
    {
        std::cout << "CO2 serial port is opened." << std::endl;
    }
    else
    {
        std::cerr << "Failed to open HUMID serial port." << std::endl;
    }

    // 서버에 전원 ON 메시지 전송
    sendMqtt2Server("rpi/admin/power/" + CLIENT_ID, "hi");

    Thread* recvMqttFromServer_t = new Thread(this, &mqtt_client, NULL, 0); // 서버로부터 MQTT 수신 스레드
    Thread* tempSensorProcess_t = new Thread(this, &mqtt_client, temp_port, 1); // 센서 데이터 수신 + 처리 스레드
    Thread* humidSensorProcess_t = new Thread(this, &mqtt_client, humid_port, 2);
    Thread* co2SensorProcess_t = new Thread(this, &mqtt_client, co2_port, 3);

    recvMqttFromServer_t->start();
    tempSensorProcess_t->start();
    humidSensorProcess_t->start();
    co2SensorProcess_t->start();

    // mqtt의 signal과 mainwindow의 slot 연결
    connect(&cb, SIGNAL(sendServerTemp(double)), this, SLOT(applyServerTemp(double)));
    connect(&cb, SIGNAL(sendServerHumid(double)), this, SLOT(applyServerHumid(double)));
    connect(&cb, SIGNAL(sendServerCo2(int)), this, SLOT(applyServerCo2(int)));

    // thread의 signal과 mainwindow의 slot 연결
    connect(tempSensorProcess_t, SIGNAL(sendTempData(double)), this, SLOT(updateTempData(double)));
    connect(humidSensorProcess_t, SIGNAL(sendHumidData(double)), this, SLOT(updateHumidData(double)));
    connect(co2SensorProcess_t, SIGNAL(sendCo2Data(int)), this, SLOT(updateCo2Data(int)));
}

// 소멸자
MainWindow::~MainWindow()
{
    mqtt::token_ptr unsubtok = mqtt_client.unsubscribe("test/1");
    unsubtok->wait();

    // Disconnect from the MQTT server
    mqtt::token_ptr disctok = mqtt_client.disconnect();
    disctok->wait();

    // Delete dynamically allocated threads
    delete recvMqttFromServer_t;
    delete tempSensorProcess_t;
    delete humidSensorProcess_t;
    delete co2SensorProcess_t;

    // 시리얼 포트 닫기
    temp_port->close();
    humid_port->close();
    co2_port->close();
    delete temp_port;
    delete humid_port;
    delete co2_port;

    delete ui;
}

// Setting 값 변경 버튼
void MainWindow::upTemperature()
{
    double tmp = ui->temp_setting_text->text().toDouble() + 0.1;
    ui->temp_setting_text->setText(QString::number(tmp, 'g', 7));
}

void MainWindow::downTemperature()
{
    double tmp = ui->temp_setting_text->text().toDouble() - 0.1;
    ui->temp_setting_text->setText(QString::number(tmp, 'g', 7));
}

void MainWindow::upHumid()
{
    double tmp = ui->humid_setting_text->text().toDouble() + 0.1;
    ui->humid_setting_text->setText(QString::number(tmp, 'g', 7));
}

void MainWindow::downHumid()
{
    double tmp = ui->humid_setting_text->text().toDouble() - 0.1;
    ui->humid_setting_text->setText(QString::number(tmp, 'g', 7));
}
void MainWindow::upCo2()
{
    int tmp = ui->co2_setting_text->text().toInt() + 1;
    ui->co2_setting_text->setText(QString::number(tmp));
}

void MainWindow::downCo2()
{
    int tmp = ui->co2_setting_text->text().toInt() - 1;
    ui->co2_setting_text->setText(QString::number(tmp));
}
void MainWindow::goLogout() // logout 함수
{
    QMessageBox msgBox;
    msgBox.setText("창 닫습니다요~~~~~~!!!");
    msgBox.exec();
    QWidget::close(); // 창 닫기
}

// 우측 센서 패널 색 바꾸기
QString color_arr[] = { "background-color: rgb(61, 91, 101);", "background-color: rgb(255, 255, 0);", "background-color: rgb(255, 0, 255);" };
int water_point = 0;
int wind_point = 0;
int sun_point = 0;
int cloud_point = 0;
void MainWindow::changeWaterColor() // 누르면 색 바뀌도록
{
    water_point = (water_point + 1) % 3;
    ui->show_water->setStyleSheet(color_arr[water_point]);
}
void MainWindow::changeWindColor() // 누르면 색 바뀌도록
{
    wind_point = (wind_point + 1) % 3;
    ui->show_wind->setStyleSheet(color_arr[wind_point]);
}
void MainWindow::changeSunColor() // 누르면 색 바뀌도록
{
    sun_point = (sun_point + 1) % 3;
    ui->show_sun->setStyleSheet(color_arr[sun_point]);
}
void MainWindow::changeCloudColor() // 누르면 색 바뀌도록
{
    cloud_point = (cloud_point + 1) % 3;
    ui->show_co2->setStyleSheet(color_arr[cloud_point]);
}

void MainWindow::changeValue() // 변경 버튼 눌렀을 때
{
    login_D = new login_dialog;

    // login_dialog의 signal과 mainwindow의 slot 연결
    connect(login_D, SIGNAL(sendLogInResult(int)), this, SLOT(recvLogInResult(int)));

    login_D->setModal(true); // modal로 열어야 로그인 창 열려있을 때 메인 창 건드리지 못 함
    login_D->exec();
}

// 기존에 수정된 값
// 만약 비밀번호 틀리면 기존에 수정된 값으로 다시 바꿔야 한다
extern double TEMP_SET;
extern double HUMID_SET;
extern int CO2_SET;

// login_dialog로부터 값 받으면 기존의 값으로 바꿀 건지
// flag == 1이면 값 변경
// flag == -1이면 값 변경 X
void MainWindow::recvLogInResult(int flag)
{
    qDebug() << flag;

    if (flag == 1) // 값 변경됨
    {
        double new_Temp = ui->temp_setting_text->text().toDouble();
        if (TEMP_SET != new_Temp)
        {
            TEMP_SET = new_Temp;
            sendMqtt2Server("rpi/temp/set/" + CLIENT_ID, ui->temp_setting_text->text().toStdString());
            qDebug() << "set TEMP changed to " << ui->temp_setting_text->text().toStdString().c_str();
        }

        double new_Humid = ui->humid_setting_text->text().toDouble();
        if (HUMID_SET != new_Humid)
        {
            HUMID_SET = new_Humid;
            sendMqtt2Server("rpi/humid/set/" + CLIENT_ID, ui->humid_setting_text->text().toStdString());
            qDebug() << "set HUMID changed to " << ui->humid_setting_text->text().toStdString().c_str();
        }

        int new_Co2 = ui->co2_setting_text->text().toDouble();
        if (CO2_SET != new_Co2)
        {
            CO2_SET = new_Co2;
            sendMqtt2Server("rpi/co2/set/" + CLIENT_ID, ui->co2_setting_text->text().toStdString());
            qDebug() << "set CO2 changed to " << ui->co2_setting_text->text().toStdString().c_str();
        }
    }
    else // 값 변경 X, 기존 값으로 돌려놓기
    {
        ui->temp_setting_text->setText(QString::number(TEMP_SET, 'g', 7));
        ui->humid_setting_text->setText(QString::number(HUMID_SET, 'g', 7));
        ui->co2_setting_text->setText(QString::number(CO2_SET));
    }
}

// 서버로 MQTT 전송
void MainWindow::sendMqtt2Server(const std::string topic, const std::string msg)
{
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, msg);
    pubmsg->set_qos(1);

    try
    {
        mqtt::token_ptr pubtok = mqtt_client.publish(pubmsg);
        pubtok->wait();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}

// mqtt.h로부터 받는 slot
void MainWindow::applyServerTemp(double t) // mqtt.h에서 보내는 signal과 연결
{
    //qDebug() << "server TEMP applied : " << t;
    ui->temp_setting_text->setText(QString::number(t, 'g', 7));
    TEMP_SET = t;
}
void MainWindow::applyServerHumid(double h) // mqtt.h에서 보내는 signal과 연결
{
    //qDebug() << "server HUMID applied : " << h;
    ui->humid_setting_text->setText(QString::number(h, 'g', 7));
    HUMID_SET = h;
}
void MainWindow::applyServerCo2(int co) // mqtt.h에서 보내는 signal과 연결
{
    //qDebug() << "server CO2 applied : " << co;
    ui->co2_setting_text->setText(QString::number(co));
    CO2_SET = co;
}

// thread.h로부터 받는 slot
void MainWindow::updateTempData(double t)
{
    //qDebug() << "received TEMP data : " << t;
    ui->temp_recent_text->setText(QString::number(t, 'g', 7));
}
void MainWindow::updateHumidData(double h)
{
    //qDebug() << "received HUMID data : " << h;
    ui->humid_recent_text->setText(QString::number(h, 'g', 7));
}
void MainWindow::updateCo2Data(int co)
{
    //qDebug() << "received CO2 data : " << co;
    ui->co2_recent_text->setText(QString::number(co));
}
