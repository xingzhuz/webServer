#include "server.h"

const char *getFileType(const char *name)
{
    // a.jpg a.mp4 a.html
    // 自右向左查找 '.' 字符，如不存在返回 NULL
    const char *dot = strrchr(name, '.');

    if (dot == NULL)
        return "text/plain; charset=utf-8"; // 纯文本

    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";

    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";

    if (strcmp(dot, ".gif") == 0)
        return "image/gif";

    if (strcmp(dot, ".png") == 0)
        return "image/png";

    if (strcmp(dot, ".css") == 0)
        return "text/css";

    if (strcmp(dot, ".au") == 0)
        return "audio/basic";

    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";

    if (strcmp(dot, ".mp3") == 0)
        return "audio/mp3";

    // 还有一些未写

    return "text/plain; charset=utf-8";
}
