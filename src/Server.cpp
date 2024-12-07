//
// Created by Momo on 2024/11/21.
//

#include "Server.h"

void error_handling(const std::string &message)
{
    // std::cerr 内容的输出
    std::cerr << message << std::endl;
    std::exit(1);
}

void read_child_proc(int sig)
{
    pid_t PID;
    int status;

    PID = waitpid(-1, &status, WNOHANG);
    std::cout << "removed proc id " << PID << std::endl;
}

TCP_Server::TCP_Server(int port) : _port(port)
{
    this->buf.resize(1024);
    this->_server_addr.sin_family = AF_INET;
    this->_server_addr.sin_port = htons(this->_port);
    this->_server_addr.sin_addr.s_addr = INADDR_ANY;
    this->_server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 初始化信号处理函数
    memset(&this->_act, 0 ,sizeof(this->_act));
    this->_act.sa_handler = read_child_proc;
    sigemptyset(&this->_act.sa_mask);
    this->_act.sa_flags = 0;

    if (this->_server_sockfd == -1)
        error_handling("服务器初始化失败...\n");
    else
        std::cout << "服务器初始化完毕\n";
}

void TCP_Server::bind_addr_info() {
        if (bind(this->_server_sockfd, (sockaddr *)&this->_server_addr, 
                sizeof(this->_server_addr)) == -1) { error_handling("bind() Error"); }
        else {
            std::cout << "绑定成功\n";
        }
}

void TCP_Server::start_listening() {
        socklen_t client_addr_len = sizeof(_client_addr);
        if (listen(this->_server_sockfd, 5) == -1) {
            error_handling("listen error");
        }
        else {
            std::cout << "Starting Listen on Port : " 
            << this->_port << std::endl;
        }
}

void TCP_Server::handle_with_client(){
    while (true) {
        socklen_t client_addr_len = sizeof(this->_client_addr);
        this->_client_sockfd = accept(_server_sockfd, (sockaddr *)&this->_client_addr, &client_addr_len);
        if (this->_client_sockfd == -1) {
            continue;
        }
        else {
            std::cout << "new clietn connected from - IP " 
                << inet_ntoa(this->_client_addr.sin_addr) 
                << " : "
                << " PORT "
                << ntohs(this->_client_addr.sin_port)
                << std::endl;   
        }

        //  捕捉子进程结束信号
        if (sigaction(SIGCHLD, &this->_act, 0) == -1) {
            close(this->_client_sockfd);
            std::cout << "sign 创建失败\n";
            continue;    
        } 
        
        pid_t PID = fork();
        // 创建子进程失败
        if (PID == -1)
        {
            close(this->_client_sockfd);
            continue;
        }
        if (PID == 0){
            close(this->_server_sockfd);
            // 处理客户端通信
            while (true) {
                auto recv_len = recv(_client_sockfd, buf.data(), buf.size(), 0);
                if (recv_len > 0) {
                    std::string reply(buf.data(), recv_len);
                    std::cout << "The Client says: " << reply << std::endl;
                    auto send_len = send(_client_sockfd, reply.c_str(), reply.size(), 0);
                    if (send_len == -1)
                        error_handling("Send Error");
                }
                else if (recv_len == 0) {
                    std::cout << "The Client disconnecting... \n";
                    break;
                }
                else
                    error_handling("Recv Error");
            }
            close(_client_sockfd);
        }
        else {
            close(this->_client_sockfd);
        }
    }
}