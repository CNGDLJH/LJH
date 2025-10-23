#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 6666           // 监听端口
#define BUFFER_SIZE 1024    // 缓冲区大小

int main() {
    // 1. 初始化Winsock环境
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // 2. 创建服务器套接字
    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. 配置服务器地址结构
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 绑定到所有网卡
    server_addr.sin_port = htons(PORT);       // 端口转换为网络字节序

    // 4. 绑定套接字到地址和端口
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 5. 监听连接请求
    if (listen(server_fd, 1) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Waiting for client connection...\n");

    // 6. 接受客户端连接
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    SOCKET client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Connected to client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // 7. 接收客户端消息
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        printf("Bytes received: %d\n", bytes_received);
        printf("Message: %s\n", buffer);
    } else {
        printf("Recv failed: %d\n", WSAGetLastError());
    }

    // 8. 关闭套接字并清理Winsock环境
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();
    printf("Server Exit.\n");

    return 0;
}
