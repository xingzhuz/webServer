#include "server.h"

// 解析请求行
int parseRequestLine(const char *line, int cfd)
{
    // 解析请求行 get /xxx/1.jpg http/1.1
    char method[12];
    char path[1024];
    sscanf(line, "%[^ ] %[^ ]", method, path);
    if (strcasecmp(method, "get") != 0) // 这个比较忽略大小写
    {
        // 这里只处理 get 请求
        return -1;
    }

    // 处理中文编码问题
    decodeMsg(path, path);

    // 处理客户端请求的静态资源(目录或者文件)
    char *file = NULL;
    if (strcmp(path, "/") == 0)
    {
        // 说明只有当前资源目录
        file = "./";
    }
    else
    {
        // 说明目录中存在当前资源目录中的子目录
        // 去掉 '/' 就能是相对路径了，就成功了，或者在开头加个 '.' 也行
        file = path + 1;
    }

    // printf("%s\n", file);
    // 获取文件属性
    struct stat st;
    int ret = stat(file, &st);
    if (ret == -1)
    {
        // 文件不存在 -- 回复 404
        // 最后一个参数设置为 -1，让浏览器自己计算长度
        sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), -1);
        sendFile("404.html", cfd); // 这个 html 需要当前资源目录下的 html文件(自己部署)
        return 0;
    }
    // 判断文件类型
    if (S_ISDIR(st.st_mode))
    {
        // 把这个目录中的内容发送给客户端
        sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1);
        sendDir(file, cfd);
    }
    else
    {
        // 把文件的内容发送给客户端
        sendHeadMsg(cfd, 200, "OK", getFileType(file), st.st_size);
        sendFile(file, cfd);
    }
}
