#include <stdio.h>
#include <string.h>
#include <winsock2.h>  // Windows 网络编程头文件
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  // 链接Winsock库

#define SERVER_IP "192.168.126.19"  // 服务器IP（需替换为实际值）
#define PORT 6666                   // 服务器端口
#define BUFFER_SIZE 1024            // 缓冲区大小

int main() {
    // 1. 初始化Winsock环境
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // 2. 创建客户端套接字
    SOCKET client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_fd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. 配置服务器地址结构
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        printf("Invalid address or address conversion failed\n");
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // 4. 发起连接
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }
    printf("Successfully connected to server: %s:%d\n", SERVER_IP, PORT);

    // 5. 发送消息（示例）
    char* message = "Hello from Dev-C++ client!";
    int bytes_sent = send(client_fd, message, strlen(message), 0);
    if (bytes_sent > 0) {
        printf("Bytes sent: %d\nMessage: %s\n", bytes_sent, message);
    } else {
        printf("Send failed: %d\n", WSAGetLastError());
    }

    // 6. 关闭套接字并清理Winsock环境
    closesocket(client_fd);
    WSACleanup();
    printf("Client exited successfully.\n");

    return 0;
}
