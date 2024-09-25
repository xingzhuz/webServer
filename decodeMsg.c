#include "server.h"

// 将字符转换为整形数
int hexToDec(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

// 解码
//  to 存储解码之后的数据，传出参数，from被解码的数据，传入参数
void decodeMsg(char *to, char *from)
{
    for (; *from != '\0';)
    {
        // isxdigit -> 判断字符是不是16进制格式，取值在 0-f
        if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))
        {
            // 将 16进制的数 -> 十进制 将这个数值赋值给了字符 int -> char
            *to = hexToDec(from[1]) * 16 + hexToDec(from[2]);

            // 跳过 '%' 和后面的两个字符
            to++;
            from += 3; // 修改为3
        }
        else
        {
            // 字符拷贝，赋值
            *to = *from;
            to++;
            from++;
        }
    }
    *to = '\0'; // 添加字符串结束符
}
