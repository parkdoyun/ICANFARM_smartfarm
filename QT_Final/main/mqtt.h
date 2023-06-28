#ifndef MQTT_H
#define MQTT_H

#include <QObject>
#include <iostream>
#include <string>
#include "mqtt/async_client.h"

extern const std::string CLIENT_ID;
extern mqtt::async_client mqtt_client;
extern mqtt::connect_options connOpts;

class MqttCallback :public QObject, public virtual mqtt::callback
{
    Q_OBJECT

public:
    void connection_lost(const std::string& cause) override;
    void message_arrived(mqtt::const_message_ptr msg) override;

signals:
    void sendServerTemp(double t);
    void sendServerHumid(double h);
    void sendServerCo2(int co);
};

#endif // MQTT_H
