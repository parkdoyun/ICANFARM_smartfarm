#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QtDebug>
#include <mqtt/async_client.h>
#include <QtSerialPort/QSerialPort>

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

private slots:
    void recvMqttFromServer(mqtt::async_client* mqtt_client_);
    void tempSensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_);
    void sendMqtt2Server(mqtt::async_client* mqtt_client_, const std::string topic, const std::string msg); // 서버로 MQTT 전송

signals:
    void sendTempData(double t);
    void sendHumidData(double h);
    void sendCo2Data(int co);
};

#endif // THREAD_H
