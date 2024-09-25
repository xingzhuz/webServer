#include "server.h"

void *recvHttpRequest(void *arg)
{
    struct FdInfo *info = (struct FdInfo *)arg;

    int len = 0, total = 0;
    char tmp[1024] = {0};
    char buf[4096] = {0};

    while ((len = recv(info->fd, tmp, sizeof tmp, 0)) > 0)
    {
        if (total + len < sizeof buf)
        {
            memcpy(buf + total, tmp, len);
        }
        total += len;
    }
    // 判断数据是否被接收完毕
    if (len == -1 && errno == EAGAIN)
    {
        // 解析请求行
        char *pt = strstr(buf, "\r\n");
        int reLen = pt - buf;
        buf[reLen] = '\0';
        parseRequestLine(buf, info->fd);
    }
    else if (len == 0)
    {
        // 客户端断开了连接
        // 删除在 epoll 树上的文件描述符，因为不需要检测这个文件描述符了
        epoll_ctl(info->epfd, EPOLL_CTL_DEL, info->fd, NULL);
        close(info->fd);
    }
    else
        perror("recv");

    printf("resvMsg threadId: %ld\n", info->tid);
    free(info);
    return NULL;
}
