#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://k8a206.p.ssafy.io:3333");
const std::string CLIENT_ID("1");
const std::string TOPIC("test/" + CLIENT_ID);
const int QOS = 1;

class callback : public virtual mqtt::callback {
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    // 발행 작업이 성공적으로 전달되었는지 확인하기 위한 콜백함수 -> 필수 X
    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "Delivery complete for token: " << token->get_message_id() << std::endl;
    }
};

void publish(mqtt::async_client& client) {
    while (true) {
        std::string payload = "";
        std::cin >> payload;
        mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, payload);
        pubmsg->set_qos(QOS);

        try {
            mqtt::token_ptr pubtok = client.publish(pubmsg);
            pubtok->wait();
        }
        catch (const mqtt::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    std::cout << "Connecting to the MQTT server..." << std::endl;
    try {
        mqtt::token_ptr conntok = client.connect(connOpts);
        conntok->wait();
        std::cout << "Connected." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    publish(client);

    return 0;
}