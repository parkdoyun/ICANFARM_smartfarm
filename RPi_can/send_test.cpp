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
    int sock;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    const char* ifname = "vcan0";

    // 소켓 생성
    if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Error while creating socket");
        return 1;
    }

    strcpy(ifr.ifr_name, ifname); // CAN 인터페이스 이름 설정
    ioctl(sock, SIOCGIFINDEX, &ifr); // 소켓-네트워크 인터페이스 연결

    // 소켓 주소 구조체 초기화
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // 소켓에 주소 바인딩
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("Error in socket bind");
        return 1;
    }

    // 프레임 ID 설정
    frame.can_id = 0x123;
    char input[256];

    while (true)
    {
        std::cin.getline(input, 256);

        if (strcmp(input, "exit") == 0) break;

        int input_len = strlen(input);
        frame.can_dlc = std::min(input_len, 8);
        memcpy(frame.data, input, frame.can_dlc);

        // CAN 프레임 송신
        int nbytes = write(sock, &frame, sizeof(struct can_frame));

        if (nbytes != sizeof(struct can_frame))
        {
            perror("Error in socket write");
            return 1;
        }
    }

    close(sock);

    return 0;
}