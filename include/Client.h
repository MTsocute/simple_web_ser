//
// Created by Momo on 2024/11/21.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

#define SERVER_IP "121.43.34.47"  // 服务端 IP
#define PORT 10000  // 服务端端口

// 存储外部信息的文件夹的位置
const fs::path docPath = fs::current_path() / "../doc";

//bool ask_user_to_quit();

void client_contact_with_server(const int client_sockfd);

void error_handling(const std::string &message);

void create_txt_file(const fs::path & dirPath);

void read_txt_file(const fs::path & filePath);

#endif //CLIENT_H
