#include "server.h"

void *acceptClient(void *arg)
{
    struct FdInfo *info = (struct FdInfo *)arg;

    // 1. 建立连接
    // 第二三个参数都是客户端相关信息，不需要知道，直接指定为 NULL
    int cfd = accept(info->fd, NULL, NULL);
    if (cfd == -1)
    {
        perror("accept");
        return NULL;
    }

    // 2. 设置非阻塞
    int flag = fcntl(cfd, F_GETFL); // 第二个参数表示得到当前文件描述符属性
    flag |= O_NONBLOCK;             // 将非阻塞属性 O_NONBLOCK 追加进去
    fcntl(cfd, F_SETFL, flag);      // 重新设置文件描述符的属性，即 flag

    // 3. cfd 添加到 epoll 中
    struct epoll_event ev;
    ev.data.fd = cfd;
    // 这个加的属性 EPOLLET 表示设置这个通信的文件描述符对应的处理事件为边沿触发模式
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(info->epfd, EPOLL_CTL_ADD, cfd, &ev);
    if (ret == -1)
    {
        perror("epoll_ctl");
        return NULL;
    }

    printf("acceptClient threadId: %ld\n", info->tid);
    free(info);
    return 0;
}