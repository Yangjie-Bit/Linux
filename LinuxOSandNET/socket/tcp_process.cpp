/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：tcp_process.cpp
 * 创 建 者: yangjie
 * 创建日期: 2020.1.13
 * 描    述: tcp服务端通信流程
 *           1. 创建套接字;
 *           2. 为套接字绑定地址信息;
 *           3. 开始监听;
 *           4. 获取已完成连接的socket;
 *           5. 通过获取的新建socket与客户端进行通信--接收数据;
 *           6. 发送数据;
 *           7. 关闭套接字
 * =============================================================*/

#include <stdio.h>
#include "tcpsocket.hpp"
#include <signal.h>
#include <sys/wait.h>

void sigcb(int no)
{
  // 如果没有僵尸进程可以处理, 就一直处理;
  // 如果没有子进程退出, 则waitpid返回0, 退出循环;
  while(waitpid(-1, NULL, WNOHANG) > 0 );
}

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::err << "./tcp_ser ip port\n";
    return -1;
  }
  signal(SIGCHLD, sigcb);
  TcpSocket lst_sock;
  // 1. 创建套接字
  CHECK_RET(lst_sock.Socket());
  // 2. 为套接字绑定地址信息
  CHECK_RET(lst_sock.Bind(argv[1],argv[2]));
  // 3. 开始监听
  CHECK_RET(lst_sock.Listen());
  while(1)
  {
    // 4. 获取已完成连接socket
    TcpSocket clisock;
    bool ret = lst_sock.Accept(clisock);
    if(ret == false)
    {
      continue;
    }
    if(fork() == 0)
    {
      while(1)
      {
        // 5. 通过获取的新建socket与客户端进行通信--接收数据
        std::string buf;
        clisock.Recv(buf);
        std::cout << "client say: " << buf << std::endl;
        // 6. 发送数据
        buf.clear();
        std::cout << "server say: ";
        fflush(stdout);
        std::cin >> buf;
        clisock.Send(buf);
      }
      clisocket.Close();
    }
    clisock.Close();
  }
  lst_sock.Close();
  return 0;
}



