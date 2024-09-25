#include "server.h"

int epollRun(int lfd)
{
    // 1. 创建 epoll 实例
    int epfd = epoll_create(1); // 1 这个参数已被弃用，随便写一个大于 0 的数即可
    if (epfd == -1)
    {
        perror("epoll_create");
        return -1;
    }

    // 2. lfd 上树
    struct epoll_event ev;
    ev.data.fd = lfd;    // data 是一个联合体，只能使用一个成员，这里使用 fd
    ev.events = EPOLLIN; // 委托内核需要检测的事件: 检测连接请求，对于服务器而言就是读事件 EPOLLIN

    // 参数: epoll id, 操作的动作, 操作的文件描述符, 事件结构体
    // 可以做三件事，增加、修改、删除
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    if (ret == -1)
    {
        perror("epoll_ctl");
        return -1;
    }

    // 3. 检测
    struct epoll_event evs[1024];
    int size = sizeof(evs) / sizeof(struct epoll_event);
    while (1)
    {
        // 检测添加到 epoll 树上的文件描述符事件是否被激活，也就是是否有事件到达
        // 第四个参数是阻塞时长，如果为 -1 就是一直阻塞
        int num = epoll_wait(epfd, evs, size, -1);
        for (int i = 0; i < num; i++)
        {
            struct FdInfo *info = (struct FdInfo *)malloc(sizeof(struct FdInfo));
            int fd = evs[i].data.fd;
            info->epfd = epfd;
            info->fd = fd;
            if (fd == lfd)
            {
                // 如果是监听的文件描述符，建立新连接 accept
                // 注意这里的 accept 是不会阻塞的，因为 epoll 已经检测了，只有触发了，才会在 evs 数组中
                // 这里创建多线程处理，效率更高
                pthread_create(&info->tid, NULL, acceptClient, info);
            }
            else
            {
                // 响应客户端请求，接收客户端请求
                pthread_create(&info->tid, NULL, recvHttpRequest, info);
            }
        }
    }
}