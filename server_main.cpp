#include "Server.h"

int main() {
    // 1. 创建套接字
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1) { error_handling("Socket Error"); }

    // 2. 创建地址信息
    sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. 绑定地址信息到套接字
    if ( bind(server_sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handling("Bind Error");
    }

    // 4. 开始监听
    if (listen(server_sockfd, 5) == -1) {
        error_handling("Listen Error");
    }
    else {
        std::cout << "Start Liseting on PORT : " << PORT << " ...\n";
    }

    for (size_t i = 0; i < 5; i++) {
        // 5. 获取客户端的套接字
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockfd = accept(server_sockfd, (sockaddr *)&client_addr, &client_addr_len);
        if (client_sockfd == -1)
            error_handling("Accpet Error");
        else {
            std::cout << "Connect From -> " 
                    << inet_ntoa(client_addr.sin_addr)   // 转换为字符串 IP 地址
                    << " : " 
                    << ntohs(client_addr.sin_port)       // 转换为主机字节序的端口号
                    << std::endl;
        }

        std::vector<char> buf (1024); buf.clear();
        int recv_len = recv(client_sockfd, buf.data(), buf.size(), 0);
        if (recv_len > 0) {
            // 6. 接受客户端发送的数据
            auto client_send = std::string(buf.begin(), buf.begin() + recv_len);
            std:: cout << "Client says: " << client_send << std::endl;
            // 7. 回复客户端，收到的数据
            int send_len  = send(server_sockfd, client_send.c_str(), client_send.size(), 0);
            if (send_len == -1) { error_handling("Reply Error"); }
        }
        else if (recv_len == 0) {
            std::cout << "Client disconnecting ...\n";
        }
        else { error_handling("Recv Error"); }

        close(client_sockfd);
    }
    
    close(server_sockfd);
    return 0;
}
