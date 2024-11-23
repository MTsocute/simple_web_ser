#include "Server.h"

extern bool KEEP_SERVER;
extern bool SHUT_SERVER;

int main() {
    int server_fd, client_fd;
    // 1. 配置好服务端的套接字和设置
    server_fd = get_server_listening_socket(PORT);

    /** 
     * 外层 while：持续监听新的客户端连接。每次接收到新的客户端连接时，进入内层逻辑
     * 内层 while：保持与当前客户端的会话，直到客户端主动断开或触发退出条件 
    **/ 

    // 2. 服务器开始监听
    while(!SHUT_SERVER) {
        std::cout << "Waiting For Connections On Port " << PORT << "...\n";
        KEEP_SERVER = true;
        
        // 3. 获取客户端套接字
        client_fd = accept_client_connection(server_fd);    
        if (client_fd == -1) {
            perror("accept failed");
            KEEP_SERVER = false;
            continue;
        }
        // 保持和当前的客户端持续的交互
        while(KEEP_SERVER) {
            // 4. 服务端和客户端交互
            server_contact_with_client(client_fd);
        }
        // 关闭套接字
        close(client_fd);
    }

    // 退出服务端
    close(server_fd);

    return 0;
}