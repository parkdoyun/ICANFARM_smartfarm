#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Create MQTT client instance
mqtt::async_client client("tcp://k8a206.p.ssafy.io:3333", "1");
mqtt::callback cb;
mqtt::connect_options connOpts;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
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
}

MainWindow::~MainWindow()
{
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
