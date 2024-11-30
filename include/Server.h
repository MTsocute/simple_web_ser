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

// 监听端口，如果你是云服务器，请确保打开服务端的防火墙
# define PORT 10000


void error_handling(const std::string &message);


#endif //SERVER_H