//
// Created by shuhe on 2024/11/22.
//

#ifndef WEB_DEMO_CLIENT_WIN_H
#define WEB_DEMO_CLIENT_WIN_H

#include <iostream>
#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h> // 包含 inet_pton 和 inet_ntop

void cleanup_winsock();


// 初始化 Winsock
void init_winsock();

#endif //WEB_DEMO_CLIENT_WIN_H
