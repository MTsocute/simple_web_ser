//
// Created by Momo on 2024/11/21.
//

#include "Server.h"

static bool KEEP_SERVER = true;

/**
 * @brief 延迟 X 秒
 * @param X_sec 多少秒 0 ~ 255
 * */ 
void delay_X_Second(uint8_t X_sec) {
    std::this_thread::sleep_for(std::chrono::seconds(X_sec));
}

/**
 * @brief 创建监听套接字
 * @param port 监听用的端口
 * @return ldf 服务端 socket
 */
int createListeningSocket(int port) {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // 使用指定端口
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(lfd, (struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        perror("bind");
        close(lfd);
        return -1;
    }

    ret = listen(lfd, 128);
    if (ret == -1) {
        perror("listen");
        close(lfd);
        return -1;
    }

    return lfd;
}

/**
 * @brief 开启服务端监听等待连接
 * @param lfd createListeningSocket 的返回值
 * @return 
 */
int acceptClientConnection(int lfd) {
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *) &cliaddr, &clilen);
    if (cfd == -1) {
        perror("accept");
        return -1;
    }

    std::cout << "客户端连接成功，IP: " << inet_ntoa(cliaddr.sin_addr)
            << ", Port: " << ntohs(cliaddr.sin_port) << std::endl;
    return cfd;
}

/**
 * @brief 和客户端保持通信，客户端如果使用 EXIT 会结束服务端的服务
 * @param cfd
 */
void handleClientCommunication(int cfd) {
    while (true) {
        std::vector<char> buf(1024);
        auto len = recv(cfd, buf.data(), buf.size(), 0);
        auto message = std::string(buf.data(), len);
        if (len > 0) {
            if (message == "QUIT") {
                std::cout << "客户端退出，监听新的客户端..." << std::endl;
                delay_X_Second(1);      // 确保客户端先结束，防止报错
                break;
            } else if (message == "EXIT") {
                std::cout << "服务端关闭..." << std::endl;
                KEEP_SERVER = false;
                delay_X_Second(1);
                break;
            } else {
                std::cout << "客户端say: " << message << std::endl;
                std::string reply = "Server Receive: " + message + "\n";
                send(cfd, reply.c_str(), reply.size(), 0);
            }
        } else if (len == 0) {
            std::cout << "客户端断开了连接..." << std::endl;
            break;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cout << "客户端强制退出，连接重置，等待下一个连接...\n";
            break;
        } else {
            perror("read");
            break;
        }
    }
}

/**
 * @brief 主要逻辑函数，开启服务器
 * @param port 开启服务器的具体端口
 */
void startServer(int port) {
    int lfd = createListeningSocket(port);      // 服务端
    if (lfd == -1) {
        std::cerr << "无法创建监听套接字，程序退出。" << std::endl;
        return;
    }

    std::cout << "服务端已开启..." << std::endl;

    while (KEEP_SERVER) {
        int cfd = acceptClientConnection(lfd);      // 客户端
        if (cfd == -1) {
            continue;
        }

        // 每一次和客户端建立的连接之后，告诉客户端我们建立起连接了
        send(cfd, "Server OK!", 10, 0);
        handleClientCommunication(cfd);
        close(cfd);
    }

    close(lfd);
}
