#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <chrono>
#include <signal.h>
#include <thread>

void cansend(int sock_fd, struct can_frame& frame) {
    frame.can_id = 0x123;
    char input[256];

    while (true)
    {
        std::cin.getline(input, 256);

        int input_len = strlen(input);
        frame.can_dlc = std::min(input_len, 8);
        memcpy(frame.data, input, frame.can_dlc);

        // CAN 프레임 송신
        ssize_t nbytes = write(sock_fd, &frame, sizeof(struct can_frame));

        if (nbytes != sizeof(struct can_frame))
        {
            perror("Error in socket write");
            return;
        }
    }
}



void candump(int sock_fd, struct can_frame& frame) {
    while (true)
    {
        ssize_t nbytes = read(sock_fd, &frame, sizeof(struct can_frame));

        if (nbytes < 0)
        {
            perror("Read error");
        }

        if (nbytes < sizeof(struct can_frame))
        {
            perror("Incomplete CAN frame");
        }

        // CAN 메시지 출력
        std::cout << "CAN ID: " << std::hex << frame.can_id << std::dec << std::endl;
        std::cout << "Data: ";
        for (int i = 0; i < frame.can_dlc; i++)
        {
            std::cout << std::hex << static_cast<int>(frame.data[i]) << " ";
        }
        std::cout << std::endl;
    }

}

int main()
{
    int sock_fd; // CAN 소켓 file descriptor
    struct sockaddr_can addr; // 소켓 주소 정보
    struct ifreq ifr; // 네트워크 디바이스를 설정하기 위한 소켓 인터페이스
    struct can_frame frame; // CAN 데이터 프레임

    const char* ifname = "vcan0";  // CAN 인터페이스 이름

    // CAN 소켓 생성
    if ((sock_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Error while creating socket");
        return 1;
    }

    strcpy(ifr.ifr_name, ifname); // CAN 인터페이스 이름 설정
    ioctl(sock_fd, SIOCGIFINDEX, &ifr); // 소켓-네트워크 인터페이스 연결

    // 소켓 주소 구조체 초기화 설정
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // 소켓에 주소 바인딩
    if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("Error in socket bind");
        return 1;
    }

    std::thread cansend_thread(cansend, sock_fd, std::ref(frame));
    std::thread candump_thread(candump, sock_fd, std::ref(frame));

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cansend_thread.join();
    candump_thread.join();

    // 소켓 닫기
    close(sock_fd);

    return 0;
}