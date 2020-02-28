/*===============================================================
 * Copyright (C) . All rights reserved.")"
 * 文件名称：
 * 创 建 者: yangjie
 * 创建日期: 2020年1月6日
 * 描    述:FILE *fopen(const char *path, const char *mode);
 *          size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
 *          size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
 *          int fseek(FILE *stream, long offset, int whence);
 *          int fclose(FILE *stream);
 * =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  // FILE *fopen(const char *path, const char *mode);
  // path: 文件路径名
  // mode: 
  // r  只读打开                            r+ 可读可写
  // w  只写,文件不存在则创建, 若文件存在则清空原有内容
  // w+ 相较于w, 多了可读操作
  // a  追加写打开, 若文件不存在则创建, 每次总是写到文件末尾
  // a+ 相较于a, 多出了可读操作
  // 返回值: 文件的操作句柄----文件流指针
  FILE* fp = fopen("tmp.txt", "w+");
  if(fp == NULL)
  {
    perror("fopen errror!");
    return -1;
  }
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
  // ptr:   要写入的元素
  // size:  要写入的块大小,--fwrite对数据进行按块操作
  // nmemb: 要写入的块个数
  // stream: fopen返回的文件流指针
  // fseek(fp,10,SEEK_END);
  char* ptr = "evething would be better!!!\n";
  size_t ret = fwrite(ptr,strlen(ptr),1,fp);                     // size_t 无符号的32位整数
  if(ret == 0)
  {
    perror("fwite errror!");
    return -1;
  }

  // int fseek(FILE *stream, long offset, int whence);
  // 对stream文件的读写位置跳转到whence位置偏移offset个字节处
  // whence: 跳转的起始位置
  // SEEK_SET   文件起始位置
  // SEEK_CUR   当前读写位置
  // SEEK_END   文件末尾位置
  // offset: 偏移量
  fseek(fp,0,SEEK_SET);

  // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  // ptr: 用于接收数据的缓冲区
  // size: 要读取的块大小
  // nmemb: 要读取的块个数
  // stream: 文件流指针
  // 返回值: 实际返回的块个数
  char buf[1024] = {0};
  ret = fread(buf,1023,1,fp);
  perror("fread error!");
  printf("ret: %d-[%s]\n",ret,&buf[2]);

  // int fclose(FILE *stream);
  fclose(fp);
  return 0;
}
