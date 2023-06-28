#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>

int sock;
struct sockaddr_can addr;
struct can_frame frame;
struct ifreq ifr;

std::string topic = "test/1";
const int QOS = 1;

const std::string CLIENT_ID("1");
const std::string PUB_TOPIC("test/" + CLIENT_ID);
const std::string SUB_TOPIC("test/" + CLIENT_ID);

class callback : public virtual mqtt::callback {
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message arrived on topic '" << msg->get_topic() << "': " << msg->to_string() << std::endl;
    }
};

// Create MQTT client instance
mqtt::async_client client("tcp://k8a206.p.ssafy.io:3333", "1");
callback cb;
mqtt::connect_options connOpts;

// MainWindow ������
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("tcp://k8a206.p.ssafy.io:3333", "1")
{
    ui->setupUi(this);

    // Set up MQTT client options
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    client.set_callback(cb);
    connOpts.set_clean_session(true);

    std::cout << "Connecting to the MQTT server..." << std::endl;
    try {
        mqtt::token_ptr conntok = client.connect(connOpts);
        conntok->wait();
        std::cout << "Connected." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    // CAN ���� ����
    if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Error while creating socket");
    }

    strcpy(ifr.ifr_name, "vcan0"); // CAN �������̽� �̸� ����
    ioctl(sock, SIOCGIFINDEX, &ifr); // ����-��Ʈ��ũ �������̽� ����

    // ���� �ּ� ����ü �ʱ�ȭ
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // ���Ͽ� �ּ� ���ε�
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error in socket bind");
    }

    Thread* mqtt_pub_t = new Thread(this, &client, NULL, topic, 0, 0);
    Thread* mqtt_sub_t = new Thread(this, &client, NULL, topic, 0, 1);
    Thread* cansend_t = new Thread(this, NULL, &frame, "", sock, 2);
    Thread* candump_t = new Thread(this, NULL, &frame, "", sock, 3);

    mqtt_pub_t->start();
    mqtt_sub_t->start();
    cansend_t->start();
    candump_t->start();
}

// MainWindow �Ҹ���
MainWindow::~MainWindow()
{
    mqtt::token_ptr unsubtok = client.unsubscribe("test/1");
    unsubtok->wait();

    // Disconnect from the MQTT server
    mqtt::token_ptr disctok = client.disconnect();
    disctok->wait();

    // Delete dynamically allocated threads
    delete mqtt_pub_t;
    delete mqtt_sub_t;
    delete cansend_t;
    delete candump_t;

    delete ui;
}

void MainWindow::subscribe_btn()
{
    QString s = ui->text->toPlainText();
    std::string send_s = s.toStdString();

    mqtt::message_ptr pubmsg = mqtt::make_message("test/1", send_s);
    pubmsg->set_qos(1);

    try {
        mqtt::token_ptr pubtok = client.publish(pubmsg);
        pubtok->wait();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.exec();
}