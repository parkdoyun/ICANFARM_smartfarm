#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <signal.h>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://k8a206.p.ssafy.io:3333");
const std::string CLIENT_ID("1");
const std::string PUB_TOPIC("rpi/test/" + CLIENT_ID);
const std::string SUB_TOPIC("server/test/" + CLIENT_ID);
const int QOS = 1;

volatile int is_running = 1;

class callback : public virtual mqtt::callback {
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message arrived on topic '" << msg->get_topic() << "': " << msg->to_string() << std::endl;
    }

    // 발행 작업이 성공적으로 전달되었는지 확인하기 위한 콜백함수 -> 필수 X
    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "Delivery complete for token: " << token->get_message_id() << std::endl;
    }
};

void publish(mqtt::async_client& client) {
    std::string payload;

    while (true) {
        std::getline(std::cin, payload);

        if (payload == "") continue;

        if (payload == "exit") {
            client.stop_consuming(); // 구독 취소 및 메시지 송신 중단
            is_running = 0;
            return;
        }

        mqtt::message_ptr pubmsg = mqtt::make_message(PUB_TOPIC, payload);
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

void subscribe(mqtt::async_client& client) {
    std::cout << "Subscribing to topic '" << SUB_TOPIC << "'..." << std::endl;
    try {
        mqtt::token_ptr subtok = client.subscribe(SUB_TOPIC, QOS);
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
    // Create MQTT client instance
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    // Set callback functions
    callback cb;
    client.set_callback(cb);

    // Create MQTT connection options object
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true); // 클라이언트가 연결을 종료할 때 브로커는 수신한 모든 메시지를 삭제

    // Connect to MQTT broker
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

    // Start thread
    std::thread subscribe_thread(subscribe, std::ref(client));
    std::thread publish_thread(publish, std::ref(client));

    while (is_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    publish_thread.join();
    subscribe_thread.join();

    // Unsubscribe
    mqtt::token_ptr unsubtok = client.unsubscribe(SUB_TOPIC);
    unsubtok->wait();
    std::cout << "Unsubscribed." << std::endl;

    // Disconnect from MQTT broker
    mqtt::token_ptr disconntok = client.disconnect();
    disconntok->wait();
    std::cout << "Disconnected." << std::endl;

    return 0;
}