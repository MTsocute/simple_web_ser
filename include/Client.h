//
// Created by Momo on 2024/11/21.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <thread>
#include <chrono>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_IP "121.43.34.47"  // 服务端 IP
#define PORT 10000  // 服务端端口

//bool ask_user_to_quit();

void client_contact_with_server(const int client_sockfd);

#endif //CLIENT_H
