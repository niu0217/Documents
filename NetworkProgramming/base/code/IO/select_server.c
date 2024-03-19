#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>

#define BACKLOG 5
#define BUFF_SIZE 200
#define DEFAULT_PORT 6666

typedef struct {
    int fd;                  /* client's connection descriptor */
    struct sockaddr_in addr; /* client's address */
} CLIENT;

int main(int argc, char *argv[])
{
    int SERVER_PORT = DEFAULT_PORT;

    if (argc > 2)
        printf("param err:\nUsage:\n\t%s port | %s\n\n", argv[0], argv[0]);
    if (argc == 2)
        SERVER_PORT = atoi(argv[1]);

    int i;
    int maxi;
    int maxfd;
    int nready;
    int nbytes;
    int servSocket;
    int cliSocket;

    // 定义fd_set集合
    fd_set allset;
    fd_set rset;

    socklen_t addrLen;
    char buffer[BUFF_SIZE];
    CLIENT client[FD_SETSIZE]; /* FD_SETSIZE == 1024 */
    struct sockaddr_in servAddr;
    struct sockaddr_in cliAddr;

    if ((servSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
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
        printf("bind");
        exit(1);
    }

    if (listen(servSocket, BACKLOG) < 0) {
        printf("listen err");
        exit(1);
    }
    printf("Listen Port: %d\nListening ...\n", SERVER_PORT);

    maxi = -1;
    maxfd = servSocket;
    // 把自定义的client数组中的fd都初始化为-1
    for (i = 0; i < FD_SETSIZE; i++)
        client[i].fd = -1; /* -1 indicates available entry */

	// 清空allset集合的标志位
    FD_ZERO(&allset);
    // 把监听socket放入这个集合中
    FD_SET(servSocket, &allset);

    for (;;) {
        rset = allset;

		// 定义两秒的超时时间
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

		// 这个只关注可读状态的描述符，并设置固定的超时时间
        nready = select(maxfd + 1, &rset, NULL, NULL, &timeout);
        // 出错返回-1
        if (nready < 0) {
            perror("select");
            break;
        }

        // 超时时间到了返回0
        else if (nready == 0) {
            printf("select time out\n");
            continue;
        }

        // 关注的描述符可操作，返回值>0
        // select返回的是整个集合，检查监听的socket是否可读
        if (FD_ISSET(servSocket, &rset)) {
            addrLen = sizeof(cliAddr);
            // 监听的socket可读，直接调用accept接收请求
            if ((cliSocket = accept(servSocket, (struct sockaddr *)&cliAddr, &addrLen)) < 0) {
                perror("accept");
                exit(1);
            }

            printf("\nNew client connections %s:%d\n", inet_ntoa(cliAddr.sin_addr),
                   ntohs(cliAddr.sin_port));

            // 保存客户端连接的socket，放在之前定义的client数组中
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i].fd < 0) {
                    client[i].fd = cliSocket;
                    client[i].addr = cliAddr;
                    break;
                }
            }

            if (i == FD_SETSIZE)
                perror("too many clients");

            // 把刚刚接收的连接描述符放在关注集合中
            FD_SET(cliSocket, &allset);
            if (cliSocket > maxfd)
                maxfd = cliSocket; /* for select */

            if (i > maxi)
                maxi = i; /* max index in client[] array */

            if (--nready <= 0)
                continue; /* no more readable descriptors */
        }

		// 上一步处理了新连接，这里处理已有连接可读的socket
		// 遍历所有的客户连接socket
        for (i = 0; i <= maxi; i++)
        {
            if ((cliSocket = client[i].fd) < 0)
                continue;

			// 依次检查每一个客户连接是否可读
            if (FD_ISSET(cliSocket, &rset)) {
                memset(buffer, 0, BUFF_SIZE);

                // 当前客户连接可读则直接使用recv接收数据
                nbytes = recv(cliSocket, buffer, sizeof(buffer), 0);
                if (nbytes < 0) {
                    perror("recv");
                    continue;
                }
                // recv返回0表示客户端断开连接
                else if (nbytes == 0) {
                    printf("\nDisconnect %s:%d\n", inet_ntoa(client[i].addr.sin_addr),
                           ntohs(client[i].addr.sin_port));
                    close(cliSocket);
                    // 把此客户端连接从关注集合中清除
                    FD_CLR(cliSocket, &allset);
                    client[i].fd = -1;
                } else {
                    printf("\nFrom %s:%d\n", inet_ntoa(client[i].addr.sin_addr),
                           ntohs(client[i].addr.sin_port));
                    printf("Recv: %sLength: %d\n\n", buffer, nbytes);
                }

                if (--nready <= 0)
                    break; /* no more readable descriptors */
            }
        }
    }
}

