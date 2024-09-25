#include "server.h"

// 发送响应头
int sendHeadMsg(int cfd, int status, const char *descr, const char *type, int length)
{
    // 状态行
    char buf[4096] = {0};
    sprintf(buf, "http/1.1 %d %s\r\n", status, descr);

    // 响应头
    sprintf(buf + strlen(buf), "content-type: %s\r\n", type);
    sprintf(buf + strlen(buf), "content-length: %d\r\n\r\n", length); // 注意两个\r\n

    send(cfd, buf, strlen(buf), 0);
    return 0;
}
