#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"  // 服务器IP（本机回环地址）
#define PORT 6666              // 服务器监听端口
#define BUFFER_SIZE 1024       // 缓冲区大小

int main() {
    // 1. 创建客户端套接字
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. 配置服务器地址结构
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address conversion failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // 3. 连接服务器
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Successfully connected to server: %s:%d\n", SERVER_IP, PORT);

    // 4. 发送消息到服务器
    char* message = "Hello from the simplified client!";
    int bytes_sent = send(client_fd, message, strlen(message), 0);
    if (bytes_sent > 0) {
        printf("Bytes sent: %d\n", bytes_sent);
        printf("Message sent: %s\n", message);
    } else {
        perror("Send failed");
    }

    // 5. 关闭套接字，释放资源
    close(client_fd);
    printf("Client exited successfully.\n");

    return 0;
}
