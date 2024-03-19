#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/epoll.h>

#define BACKLOG 5
#define BUFF_SIZE 200
#define DEFAULT_PORT 6666
#define MAX_EVENTS 10

int main(int argc, char *argv[])
{
    int SERVER_PORT = DEFAULT_PORT;

    if (argc > 2)
        printf("param err:\nUsage:\n\t%s port | %s\n\n", argv[0], argv[0]);
    if (argc == 2)
        SERVER_PORT = atoi(argv[1]);

    int nbytes;
    char buffer[BUFF_SIZE];

    int servSocket, cliSocket;
    socklen_t addrLen;
    struct sockaddr_in servAddr, cliAddr;

    struct epoll_event ev;
    struct epoll_event readyEvents[MAX_EVENTS];
    int nfds, epollfd;

    if ((servSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket err");
        exit(1);
    }

    int optval = 1;
    if (setsockopt(servSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("setsockopt");
        exit(0);
    }

    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(servSocket, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(servSocket, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }
    printf("Listen Port: %d\nListening ...\n", SERVER_PORT);

    // 创建一个epoll实例
    if ((epollfd = epoll_create1(0)) == -1) {
        perror("epoll_create");
        exit(1);
    }

    // ev是一个临时的变量，设置关心的描述符和关心的事件，然后把此结构与epoll实例绑定
    ev.events = EPOLLIN;
    ev.data.fd = servSocket;
    // 给epoll实例感兴趣列表添加一个事件
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, servSocket, &ev) == -1) {
        perror("epoll_ctl");
        exit(1);
    }

    for (;;) {
        // 等待epollfd表示的epoll实例中的事件变化，返回准备好的事件集合readyEvents
        if ((nfds = epoll_wait(epollfd, readyEvents, MAX_EVENTS, -1)) == -1) {
            perror("epoll_wait");
            exit(1);
        }

        for (int n = 0; n < nfds; n++) {
            // 有新连接到来了
            if (readyEvents[n].data.fd == servSocket) {
                addrLen = sizeof(cliAddr);
                cliSocket = accept(servSocket, (struct sockaddr *)&cliAddr, &addrLen);
                if (cliSocket == -1) {
                    perror("accept");
                    exit(1);
                }

                printf("\nNew client connections client[%d] %s:%d\n", cliSocket,
                       inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

                ev.events = EPOLLIN | EPOLLET;  // 设置关心可读状态和边缘触发模式
                ev.data.fd = cliSocket;
                // 把心连接描述符加到epoll实例感兴趣列表
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, cliSocket, &ev) == -1) {
                    perror("epoll_ctl: cliSocket");
                    exit(1);
                }
            } else {
                // 已有连接发数据过来了，开始接收数据~
                cliSocket = readyEvents[n].data.fd;

                memset(buffer, 0, BUFF_SIZE);
                /* recv data */
                nbytes = recv(cliSocket, buffer, sizeof(buffer), 0);
                if (nbytes < 0) {
                    perror("recv");
                    continue;
                } else if (nbytes == 0) {
                    printf("\nDisconnect fd[%d]\n", cliSocket);
                    close(cliSocket);
                    // 关闭文件描述符epoll实例会自动移除此描述符，
                    // 也可以使用EPOLL_CTL_DEL手动移除
                } else {
                    printf("\nFrom fd[%d]", cliSocket);
                    printf("\nRecv: %sLength: %d\n\n", buffer, nbytes);
                }
            }
        }
    }

    //    return 0;
}


