#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int main()
{
    int sock; // CAN 소켓 file descriptor
    struct sockaddr_can addr; // 소켓 주소 정보
    struct ifreq ifr; // 네트워크 디바이스를 설정하기 위한 소켓 인터페이스
    struct can_frame frame; // CAN 데이터 프레임

    const char* ifname = "vcan0"; // CAN 인터페이스 이름

    // CAN 소켓 생성
    if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Socket create failed");
        return 1;
    }

    // CAN 인터페이스 이름 설정
    strcpy(ifr.ifr_name, ifname);
    ioctl(sock, SIOCGIFINDEX, &ifr);

    // 소켓 주소 설정
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // 소켓에 바인딩
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("Socket bind failed");
        return 1;
    }

    // CAN 메시지 읽기
    while (true)
    {
        ssize_t nbytes = read(sock, &frame, sizeof(struct can_frame));

        if (nbytes < 0)
        {
            perror("Read error");
            return 1;
        }

        if (nbytes < sizeof(struct can_frame))
        {
            perror("Incomplete CAN frame");
            return 1;
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

    // 소켓 닫기
    close(sock);

    return 0;
}