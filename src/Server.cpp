//
// Created by Momo on 2024/11/21.
//

#include "Server.h"

void error_handling(const std::string &message) {
    // std::cerr 内容的输出
    std::cerr << message << std::endl;
    std::exit(1);
}