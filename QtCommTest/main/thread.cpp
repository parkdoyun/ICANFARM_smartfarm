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
    while (1)
    {
        if (serial_port_->waitForReadyRead(1000)) // 1초 동안 데이터를 기다립니다.
        {
            QString s = serial_port_->readAll(); // 들어온 모든 데이터 받습니다.
            std::string recv = s.toUtf8().constData();
            std::cout << "Serial received : " << recv << std::endl;

            try // 받은 string 데이터를 double형으로 변환
            {
                double val = stod(recv);

                // 1) 받은 데이터값 GUI에 표시
                emit sendTempData(val);

                // 2) 서버에 전송
                sendMqtt2Server(mqtt_client_, "rpi/temp/data/" + CLIENT_ID, recv);

                // 3) 세팅 온도보다 높아지면 팬 제어 명령 전송
                if (val > TEMP_SET)
                {
                    // 보내고자 하는 데이터를 작성합니다.
                    QByteArray data = "go\n";
                    // 데이터를 시리얼 포트로 전송합니다.
                    qint64 bytesWritten = serial_port_->write(data);
                    if (bytesWritten == -1)
                    {
                        qDebug() << "Failed to write the data to serial port";
                    }
                    else
                    {
                        // 내부 버퍼의 데이터를 시리얼 포트로 보냅니다.
                        serial_port_->flush();
                        std::cout << "Data send success" << std::endl;
                    }
                }
            }
            catch (const std::invalid_argument& e) // double형 변환이 안되는 인자를 받은 경우
            {
                std::cout << "Invalid argument : " << e.what() << std::endl;
            }
        }
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