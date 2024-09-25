#include "server.h"

// 发送目录
int sendDir(const char *dirName, int cfd)
{
    char buf[8192] = {0};
    sprintf(buf,
            "<html>"
            "<head>"
            "<title>%s</title>"
            "<style>"
            "body { font-family: Arial, sans-serif; margin: 20px; background-color: #f4f4f4; }"
            "h1 { color: #2c3e50; text-align: center; }"
            "table { width: 100%%; border-collapse: collapse; margin-top: 20px; }"
            "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }"
            "th { background-color: #3498db; color: white; }"
            "tr:hover { background-color: #e7f3ff; }"
            "a { text-decoration: none; color: #3498db; transition: color 0.3s; }"
            "a:hover { color: #2980b9; text-decoration: underline; }"
            "</style>"
            "</head>"
            "<body><h1>%s</h1><table><tr><th>名称</th><th>大小 (字节)</th></tr>",
            dirName, dirName);

    struct dirent **namelist;
    // 第三个参数是回调函数，表示遍历时过滤的规则， 第四个参数是排序的方式
    int num = scandir(dirName, &namelist, NULL, alphasort);
    // 虽然 namelist 定义时没有分配地址，但是在函数调用后就分配了地址，所以后续要释放内存

    for (int i = 0; i < num; i++)
    {
        // 取出文件名，namelist 指向的是一个指针数组
        char *name = namelist[i]->d_name;
        struct stat st;
        char subPath[1024] = {0};
        sprintf(subPath, "%s/%s", dirName, name);
        stat(subPath, &st);

        if (S_ISDIR(st.st_mode))
        {
            sprintf(buf + strlen(buf),
                    "<tr><td><a href=\"%s/\">%s</a></td><td>%ld</td></tr>",
                    name, name, st.st_size);
        }
        else
        {
            sprintf(buf + strlen(buf),
                    "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>",
                    name, name, st.st_size);
        }

        send(cfd, buf, strlen(buf), 0);
        memset(buf, 0, sizeof buf);
        free(namelist[i]);
    }

    sprintf(buf, "</table></body></html>");
    send(cfd, buf, strlen(buf), 0);
    free(namelist);
    return 0;
}
