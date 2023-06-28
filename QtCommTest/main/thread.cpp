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

        mqtt_client_->start_consuming(); // �޽��� ���� ���
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
        if (serial_port_->waitForReadyRead(1000)) // 1�� ���� �����͸� ��ٸ��ϴ�.
        {
            QString s = serial_port_->readAll(); // ���� ��� ������ �޽��ϴ�.
            std::string recv = s.toUtf8().constData();
            std::cout << "Serial received : " << recv << std::endl;

            try // ���� string �����͸� double������ ��ȯ
            {
                double val = stod(recv);

                // 1) ���� �����Ͱ� GUI�� ǥ��
                emit sendTempData(val);

                // 2) ������ ����
                sendMqtt2Server(mqtt_client_, "rpi/temp/data/" + CLIENT_ID, recv);

                // 3) ���� �µ����� �������� �� ���� ��� ����
                if (val > TEMP_SET)
                {
                    // �������� �ϴ� �����͸� �ۼ��մϴ�.
                    QByteArray data = "go\n";
                    // �����͸� �ø��� ��Ʈ�� �����մϴ�.
                    qint64 bytesWritten = serial_port_->write(data);
                    if (bytesWritten == -1)
                    {
                        qDebug() << "Failed to write the data to serial port";
                    }
                    else
                    {
                        // ���� ������ �����͸� �ø��� ��Ʈ�� �����ϴ�.
                        serial_port_->flush();
                        std::cout << "Data send success" << std::endl;
                    }
                }
            }
            catch (const std::invalid_argument& e) // double�� ��ȯ�� �ȵǴ� ���ڸ� ���� ���
            {
                std::cout << "Invalid argument : " << e.what() << std::endl;
            }
        }
    }
}

// ������ MQTT ����
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