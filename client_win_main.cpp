//
// Created by shuhe on 2024/11/22.
//

#include "Client_Win.h"

extern std::vector<char> buf;


int main() {
    // 初始化 Winsock
    init_winsock();

    // 1. 创建套接字
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        cleanup_winsock();
        return -1;
    }

    // 2. 设置服务端的配置
    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(10000);
    inet_pton(AF_INET, "121.43.34.47", &server_addr.sin_addr);

    // 3. 连接服务器
    int connect_stat = connect(sockfd, (sockaddr *) &server_addr, sizeof(server_addr));
    if (connect_stat == SOCKET_ERROR) {
        std::cerr << "Connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        cleanup_winsock();
        return -1;
    }

    std::cout << "成功连接服务器！\n";

    // 接收服务器的初始回复
    int connect_ok = recv(sockfd, buf.data(), buf.size(), 0);
    if (connect_ok > 0) {
        std::cout << "服务器回复: "
                  << std::string(buf.begin(), buf.begin() + connect_ok) << std::endl;
    } else if (connect_ok == 0) {
        std::cout << "服务器关闭连接...\n";
    } else {
        std::cerr << "Recv failed with error: " << WSAGetLastError() << std::endl;
    }

    // 4. 和服务器交互
    while (true) {
        std::string msg_to_ser; // 要发给服务端的内容
        std::getline(std::cin, msg_to_ser);

        // 发送数据到服务器
        int send_stat = send(sockfd, msg_to_ser.c_str(), msg_to_ser.size(), 0);
        if (send_stat == SOCKET_ERROR) {
            std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
            break;
        } else {
            // 如果输入为 "QUIT"，则退出循环并关闭连接
            if (msg_to_ser == "QUIT") {
                std::cout << "退出客户端...\n";
                break;
            }
                // 如果是 "EXIT"，服务端停止服务
            else if (msg_to_ser == "EXIT") {
                std::cout << "服务端停止服务，即将退出客户端...\n";
                break;
            }
        }

        // 接收服务器的回复
        connect_ok = recv(sockfd, buf.data(), buf.size(), 0);
        if (connect_ok > 0) {
            std::cout << "服务器reply: "
                      << std::string(buf.begin(), buf.begin() + connect_ok) << std::endl;
        } else if (connect_ok == 0) {
            std::cout << "服务器关闭连接...\n";
            break;
        } else {
            std::cerr << "Recv failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // 5. 关闭套接字
    closesocket(sockfd);

    // 清理 Winsock
    cleanup_winsock();

    return 0;
}