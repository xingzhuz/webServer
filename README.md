# webServer

> Linux 环境下简易网络服务器（Linux/多线程/epoll）


执行命令: 

```shell
# 首先查看虚拟机上的 IP 地址
ifconfig -a

# 编译运行
gcc *.c -o server
./server 10000 ./resources
```

## 简介

- 这是一个基于 `Linux` 环境下实现的网络服务器，使用 `HTTP` 协议实现浏览器和服务器通信
- 网络通信使用的 `socket` 套接字实现，还使用了 `epoll` 的非阻塞模式实现监听文件描述符
- 加入多线程提高效率

## 实现思路：

<img src="https://bu.dusays.com/2024/09/24/66f2abd5e25f4.png" height=300px, width=500px></img>

## 运行结果

1. 刚登上服务器页面


<img src="https://bu.dusays.com/2024/09/25/66f3b53ae0fd3.png"></img>

2. 点击 `code` 文件目录中的 ` cal.c ` 代码文件


<img src="https://bu.dusays.com/2024/09/25/66f3b53feffc2.png"></img>

<img src="https://bu.dusays.com/2024/09/25/66f3b54524b44.png" height=300px, width=500px></img>

3. 点击 `html` 目录中的一个 `html` 文件

<img src="https://bu.dusays.com/2024/09/24/66f2b44b0ff54.png" height=500px, width=600px></img>



4. 点击 `Image` 目录中的一个图片

<img src="https://bu.dusays.com/2024/09/24/66f2b45152c2c.png" height=300px, width=500px></img>


5. 点击 `mp3` 文件，开始播放

<img src="https://bu.dusays.com/2024/09/24/66f2b4564f1e0.png" height=300px, width=500px></img>


6. 如果是一个不存在的文件

<img src="https://bu.dusays.com/2024/09/25/66f3b551f2cf6.png" height=300px, width=500px></img>
