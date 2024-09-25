#pragma once
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/sendfile.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

// 子线程执行动作函数的参数结构体
struct FdInfo
{
    int fd;
    int epfd;
    pthread_t tid;
};

// 初始化监听的套接字
int initListenFd(unsigned short port);

// 启动 epoll
int epollRun(int lfd);

// 和客户端建立连接
// int acceptClient(int lfd, int epfd);
void *acceptClient(void *arg);

// 接收http请求
// int recvHttpRequest(int cfd, int epfd);
void *recvHttpRequest(void *arg);

// 解析请求行
int parseRequestLine(const char *line, int cfd);

// 发送文件
int sendFile(const char *fileName, int cfd);

// 发送响应头(状态行+响应头)
int sendHeadMsg(int cfd, int status, const char *descr, const char *type, int length);

// 根据文件名字或者后缀获取 HTTP 格式响应的数据类型
const char *getFileType(const char *name);

// 发送目录
int sendDir(const char *dirName, int cfd);

// 将字符转换为整形数
int hexToDec(char c);

// 解码
// to 存储解码之后的数据，传出参数，from为被解码的数据，传入参数
void decodeMsg(char *to, char *from);