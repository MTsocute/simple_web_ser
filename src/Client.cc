#include "Client.h"

static bool SEND_OR_NOT = true;
bool KEEP_CONNECTED = true;

/**
* @brief 每一次结束发送消息之后，询问客户端是否要退出
*/
bool ask_user_to_quit() {
    while (true) {
        std::cout << "Quit Connect with Server? (y/n): ";
        std::string user_input;
        std::getline(std::cin, user_input); // 读取整行输入

        // 检查输入是否合法
        if (user_input == "y" || user_input == "Y") {
            return true; // 用户选择退出
        } else if (user_input == "n" || user_input == "N") {
            return false; // 用户选择继续
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
}


/**
* @brief 客户端持续和服务器通信
* @param client_sockfd 服务器的套接字
**/
void client_contact_with_server(const int client_sockfd) {
    std::string client_message;         // 发送客户端的数据
    std::vector<char> buf(1024);      // 接受服务器的回复

    // 发送数据给服务端
    if (SEND_OR_NOT) {
        // 提示用户输入信息
        std::cout << "Client Send: ";
        std::getline(std::cin, client_message);

        // 检查输入是否为空（可选处理）
        if (client_message.empty()) {
            std::cout << "Message cannot be empty. Please enter some text." << std::endl;
            KEEP_CONNECTED = false;
        }
        send(client_sockfd, client_message.c_str(), client_message.size(), 0);
    }
    // 接受服务器发送的数据
    auto recv_status = recv(client_sockfd, buf.data(), buf.size(), 0);
    if (recv_status > 0) {
        std::cout << "Server Reply: "
                  << std::string(buf.begin(), buf.begin() + recv_status) << std::endl;
        if (client_message == "shutdown") {
            SEND_OR_NOT = false;
            return;
        }
    }
    else if (recv_status == 0) {
        std::cout << "Server is disconnecting, client is going to quit ...\n";
        KEEP_CONNECTED = false;
        return;
    } else {
        perror("send");
        KEEP_CONNECTED = false;
        return;
    }
    // 询问是否要退出
    if (ask_user_to_quit()) {
        KEEP_CONNECTED = false;
    }
}