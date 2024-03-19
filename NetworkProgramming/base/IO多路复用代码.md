# IO多路复用代码

## 参考网址

https://blog.csdn.net/shaosunrise/article/details/106957899

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

[select_server.c](https://github.com/niu0217/Documents/blob/main/NetworkProgramming/base/code/IO/select_server.c)

select的实现机制是先定义一个含有一共1024比特的long型数组的结构fd_set，用来“存放”监听的文件描述符，首先使用宏FD_ZERO把这个集合清空。然后使用宏FD_SET把需要监听的文件描述符放在这个集合中，最后调用select函数来监听这些文件描述符，可以一直阻塞等待直到有可操作的描述符才返回，也可以设置一个超时时间。
当调用select()函数的时候，内核会根据I/O状态修改与此描述符匹配的fd_set中的标志位。当select函数返回的时候，返回的是所有句柄列表，并没有告知哪个描述符准备好了。需要手动检查哪个描述符对应的标志位发生了变化，再对相应的描述符进行读写操作。

Select API：

```c
int select (int __nfds, fd_set *__readfds, fd_set *__writefds, fd_set *__exceptfds, struct timeval *__timeout);
```

+ 参数1：一般使用最大文件描述符+1
+ 参数2：关注读状态的描述符集，一般都用的这个
+ 参数3：关注写状态的描述符集，不用设置为NULL
+ 参数4：异常状态描述符集，没用过，一般设置NULL
+ 参数5：设置阻塞超时时间，这个参数有3种可能。1. 设置空指针则一直等待，2. 等待timeval指定的固定时间，3. timeval结构值为0，则每次调用都不等待。

## 2. poll

[poll_server.c](https://github.com/niu0217/Documents/blob/main/NetworkProgramming/base/code/IO/poll_server.c)

上面说到select最多只能支持1024个描述符，因为它是使用含有1024比特的long型数组的结构fd_set来“存放”监听的文件描述符，虽然可以在内核中修改此参数但是非常不方便。
为了解决这个个数限制，后来就有了poll这个模型。select的结构fd_set是固定大小的，poll使用pollfd结构的数组来传递描述符，这个数组长度可以由用户自己定义，其中一个结构标志一个描述符，这下就解决了select的个数限制问题。

Poll API：

```c
int poll (struct pollfd *__fds, unsigned long __nfds, int __timeout);
```

+ 参数1：指向一个结构数组第一个元素的指针，每个数组元素都是一个pollfd结构。
+ 参数2：上面数组中元素的个数
+ 参数3：这个超时时间和select的不太一样。这里直接使用整数值来表示等待的毫秒数，0表示立即返回不阻塞，UNP书上说INFTIM表示永远等待，但是最新的Ubuntu上面函数定义就是让设置为-1，那就设置-1吧。
+ 返回值：>0 就绪的描述符个数，=0 等待超时， <0 出错。

```c
struct pollfd {
    int fd;			/* File descriptor to poll.  */
    short int events;		/* Types of events poller cares about.  */
    short int revents;		/* Types of events that actually occurred.  */
};
```

上面是这个pollfd的结构，每个描述符使用一个此结构来标志。测试条件由events指定，函数在revents中返回该描述符的状态。即你关注什么状态就把events设置相应的值，返回的时候系统使用revents告诉用户发生了什么事情。这个状态值在系统中有宏定义。常见宏如下所示，正规TCP数据和UDP数据都被认为是普通数据。

```c
#define POLLRDNORM	0x040		/* 普通数据可读 */
#define POLLWRNORM	0x100		/* 可以写数据 */
#define POLLERR		0x008		/* 发生错误  */
```

## 3. epoll

[epoll_server.c](https://github.com/niu0217/Documents/blob/main/NetworkProgramming/base/code/IO/epoll_server.c)

虽然poll解决了select的描述符个数限制，但是实现机制都是把用户态的描述符copy到内核态，然后全部吐出来，用户手动去遍历查询。且随着数量增长，其性能也会大幅下降。于是各个平台就搞了新的I/O复用机制，Linux的是epoll，Windows的是IOCP，Unix的是Kqueue。

epoll 模型中一个重要的概念是epoll instance，epoll实例是一种内核数据结构，从用户空间来看的话，可以理解为两个list。

- **interest list (epoll set)**: 进程注册要监视的一组文件描述符。
- **ready list**: 是 interest list 中处于准备状态的一组文件描述符，由内核动态地把准备好的文件描述符放倒这个集合中。

这么看的话epoll是用一个描述符来管理多个描述符，先来看看epoll的API。

### epoll_event结构

```c
typedef union epoll_data
{
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;

struct epoll_event
{
  uint32_t events;	/* Epoll events */
  epoll_data_t data;	/* User data variable */
};

```

`epoll_event` 为用户传入的参数结构体，用户标志一个描述符。
`events`标志关注的epoll事件，在`sys.epoll.h`的`enum EPOLL_EVENTS`中有宏定义。常见宏如下

+ `EPOLLIN` ：文件描述符可以读（包括对端SOCKET正常关闭）；
+ `EPOLLOUT`：文件描述符可以写；
+ `EPOLLPRI`：文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
+ `EPOLLERR`：文件描述符发生错误；
+ `EPOLLHUP`：文件描述符被挂起；
+ `EPOLLET`： 将EPOLL设为**边缘触发(Edge Triggered)**模式，这是相对于水平触发(Level Triggered)来说的。关于触发模式接下来再细说。
+ `EPOLLONESHOT`：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

### epoll_create

```c
int epoll_create (int __size);
int epoll_create1 (int __flags);
```

`epoll_create` 创建一个新的`epoll实例`并返回此实例的描述符，`epoll_create1`与前一个功能一样，使用 FLAGS 代替未使用的 SIZE。此后的用户关心的描述符结构与此描述符进行绑定或者解绑就可以了。

### epoll_ctl

```c
int epoll_ctl (int __epfd, int __op, int __fd, struct epoll_event *__event);
```

`epoll_ctl` 注册感兴趣的文件描述符，把文件描述符添加到`epoll实例`的interest list感兴趣列表中。

### epoll_wait

```c
int epoll_wait (int __epfd, struct epoll_event *__events, int __maxevents, int __timeout);
```

epoll_wait 监听 epoll 实例_epfd中I/O事件，如果当前没有可用事件将阻塞当前线程。函数返回值为可操作的ready事件个数，第二个参数__events为ready事件结构数组指针。第三个参数一般为第二个参数的数组长度。
也就是说epoll只返回可操作性的文件描述符，而不是把所有的描述符都返回来让用户去遍历哪个可操作。