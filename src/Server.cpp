//
// Created by Momo on 2024/11/21.
//

#include "Server.h"

bool KEEP_SERVER = true;
bool SHUT_SERVER = false;

/**
 * @brief 创建监听套接字
 * @param port 监听用的端口
 * @return ldf 服务端 socket
 */
int get_server_listening_socket(const int port) {
    int server_fd;
    struct sockaddr_in address;

    // 创建服务端 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    socklen_t addrlen = sizeof(address);
    // 设置服务端地址
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // 绑定 socket 地址
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听客户端连接
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

/**
 * @brief 开启服务端监听等待连接
 * @param server_fd 服务端的套接字
 * @return 连接成功返回客户端套接字，不然就是 -1 
 */
int accept_client_connection(const int server_fd) {
    struct sockaddr_in cli_addr;       // 用于接受客户端的信息
    socklen_t cli_len = sizeof(cli_addr);
    // 获取客户端的信息
    int client_fd = accept(server_fd, (sockaddr *)&cli_addr, &cli_len);
    if (client_fd == -1) {
        return -1;
    }

    // 输出客户端的配置
    std::cout << "Client connected From IP: " << inet_ntoa(cli_addr.sin_addr)
            << " - Port: " << ntohs(cli_addr.sin_port) << std::endl;
    
    // 返回客户端的套接字
    return client_fd;
}


/**
 * @brief 进行客户端和服务器的交互
 * @param client_fd 客户端的套接字
 */
void server_contact_with_client(const int client_fd) {
    std::vector<char> buf(1024);
    int recv_status = recv(client_fd, buf.data(), buf.size(), 0);
    
    // 根据客户端不同的响应状态做出回复
    if (recv_status > 0) {
        // 输出客户端发送的内容
        int msg_len = std::move(recv_status);
        auto msg_from_client = std::string(buf.begin(), buf.begin() + msg_len);

        std::cout << "Client Say: " 
            << msg_from_client << std::endl;

        if (msg_from_client == "shutdown") {
            KEEP_SERVER = false;
            SHUT_SERVER = true;
            msg_from_client = "Server is going to shutdown..."; // 回复要退出了
            std::cout << msg_from_client << std::endl;
        }
        // 回复客户端接收到对应的数据了
        send(client_fd, msg_from_client.c_str(), msg_from_client.size(), 0);
    }
    else if (recv_status == 0) {
        std::cout << "Client Disconnecting ...\n";
        KEEP_SERVER = false;        // 客户端断开连接的时候让保持对话结束
    }
    else {
        perror("No Data Receive");
        KEEP_SERVER = false;
    }
}