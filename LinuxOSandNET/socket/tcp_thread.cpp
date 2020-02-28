/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：tcp_thread.cpp
 * 创 建 者: yangjie
 * 创建日期: 2020.1.13
 * 描    述:
 *
 * =============================================================*/

#include <stdio.h>
#include <pthread.h>
#include "tcpsocket.hpp"

int main()
{
  TcpSocket* clisock = (TcpSocket*)arg;
  while(1)
  {
    // 通过获取的新建的socket与客户端进行通信--接收数据
    std::string buf;
    clisock->Recv(buf);
    std::cout << "client say" << buf << std::endl;
    // 发送数据
    buf.clear();
    std::cout << "server say:";
    fflush(stdout);
    std::cin >> buf;
    clisock->Send(buf);
  }
  clisock->Close();
  delete clisock;
  return NULL;
}

int main()
{
  if(argc != 3 )
  {
    srd::err << "./tcp_srv ip port\n";
    return -1;
  }
  TcpSocket lst_sock;
  // 创建套接字
  CHECK_RET(lst_sock.Socket());
  // 为套接字绑定地址信息
  
}
