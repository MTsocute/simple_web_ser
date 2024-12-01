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

    std::vector<char> reply_msg(1024); reply_msg.clear();

    // TODO: 实现一个 ECHO
    while (true) {
        std::string msg_to_server;
        msg_to_server.clear();
        std::cout << "Input Something:\n";
        std::cin >> msg_to_server;

        if (msg_to_server != "q" or msg_to_server != "Q") {
            // 4. 发送数据
            auto send_len = send(client_sockfd, 
                    msg_to_server.data(), msg_to_server.size(), 0);
            if (send_len == -1) { error_handling("Send Error"); }
            // 5. 等待服务器的回应
            reply_msg.clear();
            auto recv_len = recv(client_sockfd, reply_msg.data(), reply_msg.size(), 0);
            if (recv_len == -1) { error_handling("Receive Error"); }
        }
        else {
            msg_to_server = "Client Shoutdown\n";
            auto send_len = send(client_sockfd, msg_to_server.data(), msg_to_server.size(), 0);
            if (send_len == -1) { error_handling("Send Error"); }
            break;
        }
    }

    // 6. 完成一次简单通讯，关闭通信
    close(client_sockfd);

    return 0;
}