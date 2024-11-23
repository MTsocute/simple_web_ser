#include "Client.h"

extern bool KEEP_CONNECTED;

int main() {
    int client_sockfd = 0;
    sockaddr_in serv_addr{};

    // 创建客户端 socket
    if ((client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将 IP 地址从字符串转换为网络字节序
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        return -1;
    }

    // 连接到服务端
    if (connect(client_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    std::cout << "Connected to server " << SERVER_IP << " : " << PORT << std::endl;

    // 维持服务端和客户端对话，除非自己手动退出
    while (KEEP_CONNECTED) {
        client_contact_with_server(client_sockfd);
    }

    // 关闭客户端 socket
    close(client_sockfd);
    return 0;
}
