//
// Created by Momo on 2024/11/21.
//

#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <cstring>  // memset
#include <errno.h>
#include <thread>
#include <chrono>
#include <cstdint>

//
int createListeningSocket(int port);

//
int acceptClientConnection(int lfd);

// 处理与客户端的通信
void handleClientCommunication(int cfd);

// 主服务器逻辑
void startServer(int port);


// 延迟函数
void delay_X_Second(uint8_t X_sec);

#endif //SERVER_H
    