# IO多路复用代码

## 用到的知识

### INADDR_ANY

在 Linux 的网络编程中，`htonl()` 函数用于将主机字节序转换为网络字节序。而 `INADDR_ANY` 是一个特殊的 IP 地址，表示服务器上所有网络接口的任意地址。

在网络编程中，当你想要绑定一个服务器的套接字到所有可用的网络接口时，可以使用 `htonl(INADDR_ANY)`。这个函数调用将返回一个用于绑定的特殊地址，允许服务器套接字接受来自任何网络接口的连接。

下面是一个示例，展示了如何在网络编程中使用 `htonl(INADDR_ANY)`：

```c
#include <stdio.h>
#include <netinet/in.h>

int main() {
    struct sockaddr_in server_address;
    
    // 设置服务器地址
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // 将端口号从主机字节序转换为网络字节序
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // 将IP地址设置为INADDR_ANY
    
    // 其他操作...
    
    return 0;
}
```

在上述示例中，`htonl(INADDR_ANY)` 被用来将地址设置为可以绑定到所有可用的网络接口上。这样，服务器就可以接受来自任何网络接口的连接。

## 1. select



## 2. poll



## 3. epoll

