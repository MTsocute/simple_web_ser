//
// Created by shuhe on 2024/11/22.
//

#include "Client_Win.h"


static volatile bool KEEP_CONNECTING = true;
std::vector<char> buf(1024);


void cleanup_winsock() {
    WSACleanup();
}

void init_winsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // 请求 Winsock 2.2
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        exit(1); // 如果初始化失败，退出程序
    }
}
