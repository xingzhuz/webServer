#include "server.h"

int sendFile(const char *fileName, int cfd)
{
    // 1.打开文件
    int fd = open(fileName, O_RDONLY);
    // 断言判断文件是否打开成功，如果打开失败，程序直接挂在这里，或者抛出异常
    assert(fd > 0);

#if 0
    while (1)
    {
        char buf[1024];
        int len = read(fd, buf, sizeof buf);
        if (len > 0)
        {
            send(cfd, buf, len, 0);
            usleep(10); // 这非常重要
        }
        else if (len == 0)  // 文件内容读取完毕
        {
            break;
        }
        else
        {
            perror("read");
        }
    }
#else
    off_t offset = 0;
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    while (offset < size)
    {
        int ret = sendfile(cfd, fd, &offset, size - offset);
        printf("ret value: %d\n", ret);
        if (ret == -1 && errno != EAGAIN)
        {
            perror("sendfile");
        }
    }

#endif
    return 0;
}
