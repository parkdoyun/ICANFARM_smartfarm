#include "thread.h"
#include <iostream>

Thread::Thread(QObject* parent, mqtt::async_client* mqtt_client, QSerialPort* serial_port, int num) :
    QThread(parent),
    mqtt_client_(mqtt_client),
    serial_port_(serial_port),
    num_(num)
{

}

void Thread::run()
{
    std::cout << " Thread #" << num_ << " running" << std::endl;
    if (num_ == 0) recvMqttFromServer(mqtt_client_);
    else if (num_ == 1) tempSensorProcess(mqtt_client_, serial_port_);
    else if (num_ == 2) humidSensorProcess(mqtt_client_, serial_port_);
    else if (num_ == 3) co2SensorProcess(mqtt_client_, serial_port_);
}

void Thread::recvMqttFromServer(mqtt::async_client* mqtt_client_)
{
    std::cout << "Subscribing server..." << std::endl;
    try
    {
        mqtt::token_ptr subtok = mqtt_client_->subscribe("server/#", 1); // QOS = 1
        subtok->wait();
        std::cout << "Subscribed." << std::endl;

        mqtt_client_->start_consuming(); // 메시지 수신 대기
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}

void Thread::tempSensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_)
{
    temp_flag = 0;

    connect(serial_port_, &QSerialPort::readyRead, this, [=]() {
        QString s = serial_port_->readLine();
        std::string recv = s.toUtf8().constData();
        std::cout << "TEMP Serial received : " << recv << std::endl;

        int st = -1;
        int en = -1;
        for (int i = 0; i < (int)recv.length(); i++) {
            if (recv[i] == '@') st = i;
            if (recv[i] == '#') {
                en = i;
                break;
            }
        }

        if (st != -1 && en != -1 && temp_flag == 1) temp_flag = 0;

        if (st == -1 && en != -1 && temp_flag == 1) {
            st = 0;
            std::string parsed_str = recv.substr(st, en - st);
            temp_save += parsed_str;
        }

        if (st != -1 && en != -1) {
            if (temp_flag == 1) temp_flag = 0;
            else temp_save = recv.substr(st + 1, en - st - 1);
            std::cout << "TEMP Parsed data : " << temp_save << std::endl;

            try {
                double val = stod(temp_save);

                // 1) 받은 데이터를 GUI에 표시
                emit sendTempData(val);

                // 2) 데이터를 서버로 전송
                sendMqtt2Server(mqtt_client_, "rpi/temp/data/" + CLIENT_ID, temp_save);

                // 3) 값이 설정 온도를 초과하면 팬 제어 명령 전송
                if (val > TEMP_SET) {
                    // 팬 제어를 위해 보낼 데이터 작성
                    QByteArray data = "go\n";
                    // 데이터를 시리얼 포트로 전송
                    qint64 bytesWritten = serial_port_->write(data);
                    if (bytesWritten == -1) {
                        qDebug() << "Failed to write the data to serial port";
                    }
                    else {
                        // 내부 버퍼의 데이터를 시리얼 포트로 보냄
                        serial_port_->flush();
                        qDebug() << "###### FAN control send #####";
                    }
                }
            }
            catch (const std::invalid_argument& e) {
                qDebug() << "Invalid argument : " << e.what();
            }
            temp_save.clear();
        }

        else if (st == -1 && en != -1) {
            temp_save.clear();
        }

        else if (st != -1 && en == -1) {
            temp_flag = 1;
            en = recv.length() - 1;
            temp_save = recv.substr(st + 1, en - st);
        }
        });
}

void Thread::humidSensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_)
{
    humid_flag = 0;

    connect(serial_port_, &QSerialPort::readyRead, this, [=]() {
        QString s = serial_port_->readLine();
        std::string recv = s.toUtf8().constData();
        std::cout << "HUMID Serial received : " << recv << std::endl;

        int st = -1;
        int en = -1;
        for (int i = 0; i < (int)recv.length(); i++) {
            if (recv[i] == '@') st = i;
            if (recv[i] == '#') {
                en = i;
                break;
            }
        }

        if (st != -1 && en != -1 && humid_flag == 1) humid_flag = 0;

        if (st == -1 && en != -1 && humid_flag == 1) {
            st = 0;
            std::string parsed_str = recv.substr(st, en - st);
            humid_save += parsed_str;
        }

        if (st != -1 && en != -1) {
            if (humid_flag == 1) humid_flag = 0;
            else humid_save = recv.substr(st + 1, en - st - 1);
            std::cout << "HUMID Parsed data : " << humid_save << std::endl;

            try {
                double val = stod(humid_save);

                // 1) 받은 데이터를 GUI에 표시
                emit sendHumidData(val);

                // 2) 데이터를 서버로 전송
                sendMqtt2Server(mqtt_client_, "rpi/humid/data/" + CLIENT_ID, humid_save);

                // 3) 값이 설정 습도보다 낮으면 워터펌프 제어 명령 전송
                if (val < HUMID_SET) {
                    // 팬 제어를 위해 보낼 데이터 작성
                    QByteArray data = "go\n";
                    // 데이터를 시리얼 포트로 전송
                    qint64 bytesWritten = serial_port_->write(data);
                    if (bytesWritten == -1) {
                        qDebug() << "Failed to write the data to serial port";
                    }
                    else {
                        // 내부 버퍼의 데이터를 시리얼 포트로 보냄
                        serial_port_->flush();
                        qDebug() << "##### WATER PUMP control send #####";
                    }
                }
            }
            catch (const std::invalid_argument& e) {
                qDebug() << "Invalid argument : " << e.what();
            }
            humid_save.clear();
        }

        else if (st == -1 && en != -1) {
            humid_save.clear();
        }

        else if (st != -1 && en == -1) {
            humid_flag = 1;
            en = recv.length() - 1;
            humid_save = recv.substr(st + 1, en - st);
        }
        });
}

void Thread::co2SensorProcess(mqtt::async_client* mqtt_client_, QSerialPort* serial_port_)
{
    co2_flag = 0;

    connect(serial_port_, &QSerialPort::readyRead, this, [=]() {
        QString s = serial_port_->readLine();
        std::string recv = s.toUtf8().constData();
        std::cout << "CO2 Serial received : " << recv << std::endl;

        int st = -1;
        int en = -1;
        for (int i = 0; i < (int)recv.length(); i++) {
            if (recv[i] == '@') st = i;
            if (recv[i] == '#') {
                en = i;
                break;
            }
        }

        if (st != -1 && en != -1 && co2_flag == 1) co2_flag = 0;

        if (st == -1 && en != -1 && co2_flag == 1) {
            st = 0;
            std::string parsed_str = recv.substr(st, en - st);
            co2_save += parsed_str;
        }

        if (st != -1 && en != -1) {
            if (co2_flag == 1) co2_flag = 0;
            else co2_save = recv.substr(st + 1, en - st - 1);
            std::cout << "CO2 Parsed data : " << co2_save << std::endl;

            try {
                int val = stoi(co2_save);

                // 1) 받은 데이터를 GUI에 표시
                emit sendCo2Data(val);

                // 2) 데이터를 서버로 전송
                sendMqtt2Server(mqtt_client_, "rpi/co2/data/" + CLIENT_ID, co2_save);
            }
            catch (const std::invalid_argument& e) {
                qDebug() << "Invalid argument : " << e.what();
            }
            co2_save.clear();
        }

        else if (st == -1 && en != -1) {
            co2_save.clear();
        }

        else if (st != -1 && en == -1) {
            co2_flag = 1;
            en = recv.length() - 1;
            co2_save = recv.substr(st + 1, en - st);
        }
        });

    // 시간 확인 -> LED 제어
    time_t rawTime;
    struct tm* pTimeInfo;

    while (1) {
        rawTime = time(NULL);
        pTimeInfo = localtime(&rawTime);
        int hour = pTimeInfo->tm_hour;

        QByteArray data;
        if (5 <= hour && hour <= 17) {
            data = "1";
        }
        else {
            data = "0";
        }

        qint64 bytesWritten = serial_port_->write(data);
        if (bytesWritten == -1)
        {
            qDebug() << "Failed to write the data to serial port";
        }
        else
        {
            // 내부 버퍼의 데이터를 시리얼 포트로 보냅니다.
            serial_port_->flush();
            std::cout << "##### LED control send #####" << std::endl;
        }

        std::cout << "Now hour : " << hour << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

// 서버로 MQTT 전송
void Thread::sendMqtt2Server(mqtt::async_client* mqtt_client_, const std::string topic, const std::string msg)
{
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, msg);
    pubmsg->set_qos(1);

    try
    {
        mqtt::token_ptr pubtok = mqtt_client_->publish(pubmsg);
        pubtok->wait();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}
