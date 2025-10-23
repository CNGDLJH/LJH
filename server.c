#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6666      // 监听端口
#define BUFFER_SIZE 1024  // 缓冲区大小

int main() {
    // 1. 创建服务器套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. 配置服务器地址结构
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;         // IPv4协议
    server_addr.sin_addr.s_addr = INADDR_ANY; // 绑定到所有网卡（本机所有IP）
    server_addr.sin_port = htons(PORT);       // 端口转换为网络字节序

    // 3. 绑定套接字到地址和端口
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. 监听连接请求（最多允许1个挂起连接）
    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Waiting for client connection...\n");

    // 5. 接受客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // 6. 接收客户端消息
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_received > 0) {
        printf("Bytes received: %d\n", bytes_received);
        printf("Message: %s\n", buffer);
    } else {
        perror("Read failed");
    }

    // 7. 关闭套接字，释放资源
    close(client_fd);
    close(server_fd);
    printf("Server Exit.\n");

    return 0;
}
