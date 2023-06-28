#include "mainwindow.h"
#include "./ui_mainwindow.h"

int sock;
struct sockaddr_can addr;
struct can_frame frame;
struct ifreq ifr;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ���� ����
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::subscribe_btn()
{
    frame.can_id = 0x123;

    QString s = ui->text->toPlainText();
    std::string send_s = s.toStdString();

    int input_len = send_s.length();
    frame.can_dlc = std::min(input_len, 8);
    memcpy(frame.data, send_s.c_str(), frame.can_dlc);

    // CAN ������ �۽�
    int nbytes = write(sock, &frame, sizeof(struct can_frame));

    if (nbytes != sizeof(struct can_frame)) {
        perror("Error in socket write");
    }

    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.exec();
}
