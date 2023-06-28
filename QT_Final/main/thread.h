#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QtDebug>
#include <mqtt/async_client.h>
#include <QtSerialPort/QSerialPort>
#include <time.h>
#include <unistd.h>

extern const std::string CLIENT_ID;
extern double TEMP_SET;
extern double HUMID_SET;

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(QObject* parent, mqtt::async_client* mqtt_client, QSerialPort* serial_port, int num);

private:
    void run() override;
    mqtt::async_client* mqtt_client_;
    QSerialPort* serial_port_;
    int num_;
    // 데이터 파싱용 변수들
    std::string temp_save;
    volatile int temp_flag;
    std::string humid_save;
    volatile int humid_flag;
    std::string co2_save;
    volatile int co2_flag;

private slots:
    void recvMqttFromServer(mqtt::async_client* mqtt_client_);
    void tempSensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_);
    void humidSensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_);
    void co2SensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_);
    void sendMqtt2Server(mqtt::async_client* mqtt_client_, const std::string topic, const std::string msg); // 서버로 MQTT 전송

signals:
    void sendTempData(double t);
    void sendHumidData(double h);
    void sendCo2Data(int co);
};

#endif // THREAD_H
