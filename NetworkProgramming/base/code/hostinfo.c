/* ************************************************************************
> File Name:     hostinfo.c
> Author:        niu0217
> Created Time:  Sun 17 Mar 2024 12:02:11 PM CST
> Description:
 ************************************************************************/

#include "csapp.h"

int main(int argc, char** argv)
{
    struct addrinfo* p;
    struct addrinfo* listp; //用于保存Getaddrinfo的结果
    struct addrinfo hints; //提供对Getaddrinfo返回的套接字地址列表的更好的控制
    char buf[MAXLINE]; //用于保存主机信息
    int rc;
    int flags;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    //Get a list of addrinfo records
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; //IPV4
    hints.ai_socktype = SOCK_STREAM; //TCP
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    //Walk the list and display each IP address
    flags = NI_NUMERICHOST; //返回一个数字地址字符串(而不是域名)
    for(p = listp; p; p = p->ai_next) {
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf); //因为设置了flags，所以会返回主机的数字地址字符串
    }

    //Clean up
    Freeaddrinfo(listp);
}
