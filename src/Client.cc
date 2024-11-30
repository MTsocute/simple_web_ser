#include "Client.h"

void error_handling(const std::string &message) {
    // std::cerr 内容的输出
    std::cerr << message << std::endl;
    std::exit(1);
}

void create_txt_file(const fs::path & dirPath) {
    // 父文件夹存在与否
    if (fs::exists(dirPath)) {
        std::string file_path = dirPath / "data.txt";  // 文件的完全路径
        std::string data_to_write = "fuck you linux";   // 写入的内容

        // 在对应路径创建一个文件并写入一些内容
        std::ofstream outFile(file_path,
            std::ios::out | std::ios::trunc);
        // 写入内容
        if (outFile.is_open()) {
            outFile << data_to_write;
            outFile.close();
            std::cout << "You've successfully Written sth. on data.txt\n";
        }
        else { error_handling("Write Error"); }
    }
    // 文件夹不存在，创建到这个路径的文件夹和对应的文件
    else {
        fs::create_directory(dirPath);
        if (fs::exists(dirPath)) {
            std::cout << "Successfully Creating a doc directory\n";
        }
        else { error_handling("Creating Folder Error"); }
    }
}

void read_txt_file(const fs::path & filePath) {
    if (fs::exists(filePath)) {
        // 打开文件
        std::ifstream readFile(filePath);
        // 检查是否能够读写文件
        if (!readFile) { error_handling("Failed to Open th file\n"); }

        std::string line;
        while (std::getline(readFile, line)) {
            std::cout << line << std::endl;
        }
        readFile.close();
    }
    else { error_handling("The File Doesn't exist"); }
}