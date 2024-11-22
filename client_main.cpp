#include "Client.h"

static volatile bool KEEP_CONNECTING = true;
std::vector<char> buf(1024);

int main() {
    // 1. 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }

    // 2. 设置服务端的配置
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(10000);
    inet_pton(AF_INET, "121.43.34.47", &server_addr.sin_addr);


    // 3. 连接服务器
    auto connect_stat = connect(sockfd, 
                        (sockaddr*)&server_addr, sizeof(server_addr));
    if (connect_stat == -1) {
        perror("connect");
        return -1;
    }

    std::cout << "成功连接服务器！\n";      // 告诉客户端我们建立起连接了
    auto connect_ok = recv(sockfd, buf.data(), buf.size(), 0);
    std::cout << "服务器回复: " 
        << std::string(buf.begin(), buf.begin() + connect_ok) << std::endl;    


    // 4. 和服务器交互
    while(true) {
        std::string  msg_to_ser;        // 要发给服务端的内容
        std::getline(std::cin, msg_to_ser);
        
        // 发送数据到服务器
        auto send_stat = send(sockfd, msg_to_ser.c_str(), msg_to_ser.size(), 0);
        if (send_stat == -1) {
            perror("send");
            break;
        } else {
            // 如果输入为 "QUIT"，则退出循环并关闭连接
            if (msg_to_ser == "QUIT") {
                std::cout << "退出客户端...\n";
                break;
            }
            // 如果是 "EXIT"，服务端停止服务
            else if(msg_to_ser == "EXIT") {
                std::cout << "服务端停止服务，即将退出客户端...\n";
                break;
            }
        }

        // 监听内容
        if (connect_ok > 0) {
            std::cout << "服务器reply: " 
                << std::string(buf.begin(), buf.begin() + connect_ok) << std::endl;
        } else if (connect_ok == 0) {
            std::cout << "服务器关闭连接...\n";
        } else {
            perror("recv");
        }
    }

    // 5. 关闭 socket
    close(sockfd);
    return 0;
}