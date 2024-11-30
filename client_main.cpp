#include "Client.h"

int main() {
    // 创建一个简单的客户端

    // 1. 创建套接字
    int client_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (client_sockfd == -1) {
        error_handling("Socket Error\n");
    }

    // 2. 配置服务器的 addrsock_in 
    sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // 3. 连接到服务器
    if (connect(client_sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handling("Connect Error");
    } else { std::cout << "Conneted with Server\n"; }

    // 4. 发送数据
    std::vector<char> msg(1024);
    msg.clear();
    auto send_len = send(client_sockfd, msg.data(), msg.size(), 0);
    if (send_len == -1) { error_handling("Send Error"); }

    // 5. 等待服务器的回应
    msg.clear();
    auto recv_len = recv(client_sockfd, msg.data(), msg.size(), 0);
    if (recv_len == -1) { error_handling("Receive Error"); }


    // 6. 完成一次简单通讯，关闭通信
    close(client_sockfd);

    return 0;
}