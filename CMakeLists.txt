cmake_minimum_required(VERSION 3.15)
project(web_demo)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
        message(STATUS "Configuring for Windows")
        # win 客户端
        add_executable(web_client_win
                client_win_main.cpp
                src/Client_Win.cpp
        )
        target_link_libraries(web_client_win PRIVATE ws2_32)
        target_include_directories(web_client_win PRIVATE "./include/")
        # Apple 客户端的逻辑代码
elseif(APPLE)
        message(STATUS "Configuring for macOS")
        add_executable(multi_thread ./multi_server.cpp ./src/Server.cpp)
        add_executable(client ./client_main.cpp ./src/Client.cc)
        target_include_directories(multi_thread PRIVATE "./include/")
        target_include_directories(client PRIVATE "./include/")
else()
        message(STATUS "Configuring for other OS")
        # 创建目标web_demo
        add_executable(web_server
                server_main.cpp
                src/Server.cpp
        )
        add_executable(multi_thread ./multi_server.cpp ./src/Server.cpp)
        target_include_directories(web_client PRIVATE "./include/")
        target_include_directories(multi_thread PRIVATE "./include/")
endif()
