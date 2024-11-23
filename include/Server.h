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

#define PORT 10000 // 监听端口，如果你是云服务器，请确保打开服务端的防火墙

int get_server_listening_socket(const int port);

int accept_client_connection(const int server_fd);

void server_contact_with_client(const int client_fd);


#endif //SERVER_H