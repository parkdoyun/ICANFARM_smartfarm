#include <iostream>
#include <cstring>
#include <signal.h>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://k8a206.p.ssafy.io:3333");
const std::string CLIENT_ID("1");
const std::string TOPIC("test/" + CLIENT_ID);
const int QOS = 1;

volatile sig_atomic_t is_running = 1;

void sigint_handler(int signal) {
    std::cout << "Caught signal " << signal << std::endl;
    is_running = 0;
}

class callback : public virtual mqtt::callback {
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message arrived on topic '" << msg->get_topic() << "': " << msg->to_string() << std::endl;
    }
};

void subscribe(mqtt::async_client& client) {
    std::cout << "Subscribing to topic '" << TOPIC << "'..." << std::endl;
    try {
        mqtt::token_ptr subtok = client.subscribe(TOPIC, QOS);
        subtok->wait();
        std::cout << "Subscribed." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return;
    }

    while (is_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char* argv[]) {
    // 강제종료(ctrl + C) 시그널 등록
    signal(SIGINT, sigint_handler);

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

    subscribe(client);

    // 구독 해지
    mqtt::token_ptr unsubtok = client.unsubscribe(TOPIC);
    unsubtok->wait();
    std::cout << "Unsubscribed." << std::endl;

    // 연결 끊기
    mqtt::token_ptr disconntok = client.disconnect();
    disconntok->wait();
    std::cout << "Disconnected." << std::endl;

    return 0;
}