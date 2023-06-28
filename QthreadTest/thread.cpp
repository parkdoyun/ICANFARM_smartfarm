#include "thread.h"
#include <iostream>

Thread::Thread(QObject* parent, mqtt::async_client* mqtt_client, struct can_frame* frame, const std::string topic, int sock, int num) :
    QThread(parent),
    mqtt_client_(mqtt_client),
    frame_(frame),
    topic_(topic),
    sock_(sock),
    num_(num)
{
    std::cout << "Thread run" << std::endl;
}

void MqttPub(mqtt::async_client* mqtt_client_, const std::string topic_);
void MqttSub(mqtt::async_client* mqtt_client_, const std::string topic_);
void Cansend(struct can_frame* frame_, int sock_);
void Candump(struct can_frame* frame_, int sock_);

void Thread::run()
{
    std::cout << num_ << std::endl;
    if (num_ == 0) MqttPub(mqtt_client_, topic_);
    else if (num_ == 1) MqttSub(mqtt_client_, topic_);
    else if (num_ == 2) Cansend(frame_, sock_);
    else if (num_ == 3) Candump(frame_, sock_);
}

void MqttPub(mqtt::async_client* mqtt_client_, const std::string topic_)
{
    while (1) {
        std::cout << "Publishing to topic 'test/1'..." << std::endl;
        mqtt::message_ptr pubmsg = mqtt::make_message("test/1", "MQTT TEST");
        pubmsg->set_qos(1);

        try {
            mqtt::token_ptr pubtok = mqtt_client_->publish(pubmsg);
            pubtok->wait();
        }
        catch (const mqtt::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void MqttSub(mqtt::async_client* mqtt_client_, const std::string topic_)
{
    std::cout << "Subscribing to topic 'test/1'..." << std::endl;
    try {
        mqtt::token_ptr subtok = mqtt_client_->subscribe("test/1", 1);
        subtok->wait();
        std::cout << "Subscribed." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}

void Cansend(struct can_frame* frame_, int sock_)
{
    while (1) {
        frame_->can_id = 0x123;

        std::string send_s = "CAN TEST";

        int input_len = send_s.length();
        frame_->can_dlc = std::min(input_len, 8);
        memcpy(frame_->data, send_s.c_str(), frame_->can_dlc);

        int nbytes = write(sock_, frame_, sizeof(struct can_frame));

        if (nbytes != sizeof(struct can_frame)) {
            perror("Error in socket write");
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Candump(struct can_frame* frame_, int sock_)
{
    while (1) {
        int nbytes = read(sock_, frame_, sizeof(struct can_frame));

        if (nbytes < 0)
        {
            perror("Read error");
        }

        if (nbytes < sizeof(struct can_frame))
        {
            perror("Incomplete CAN frame");
        }

        std::cout << "CAN ID: " << std::hex << frame_->can_id << std::dec << std::endl;
        std::cout << "Data: ";
        for (int i = 0; i < frame_->can_dlc; i++)
        {
            std::cout << std::hex << static_cast<int>(frame_->data[i]) << " ";
        }
        std::cout << std::endl;
    }
}