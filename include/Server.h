//
// Created by Momo on 2024/11/21.
//

#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <cstring> // memset
#include <errno.h>
#include <chrono>
#include <cstdint>

// 监听端口，如果你是云服务器，请确保打开服务端的防火墙
#define PORT 10000

void error_handling(const std::string &message);
void read_child_proc(int sig);

class TCP_Server;

class TCP_Server {
private:
    int _port;
    sockaddr_in _server_addr, _client_addr;
    int _server_sockfd, _client_sockfd;
    struct sigaction _act;
    std::string buf;
public:
    // explicit TCP_Server() = default;
    explicit TCP_Server(int port);

    TCP_Server(const TCP_Server &other) = delete;
    TCP_Server operator=(const TCP_Server &other) = delete;
    TCP_Server(TCP_Server&&) = delete;  // 禁止移动构造
    TCP_Server& operator=(TCP_Server&&) = delete;  // 禁止移动赋值

    void bind_addr_info();

    void start_listening();

    virtual void handle_with_client();

    ~TCP_Server() noexcept = default;
};

#endif // SERVER_H