cmake_minimum_required(VERSION 3.20)
project(web_demo)

set(CMAKE_CXX_STANDARD 20)

# 创建目标web_demo
add_executable(web_server server_main.cpp src/Server.cpp)

# 客户端的逻辑代码
add_executable(web_client client_main.cpp src/Client.cc)

# 指定头文件的搜索路径
target_include_directories(web_server PRIVATE "./include/")
target_include_directories(web_client PRIVATE "./include/")
