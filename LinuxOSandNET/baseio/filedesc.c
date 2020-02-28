/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：yangjie
*   创建日期：
*   描    述：体会文件描述符分配规则
*             通过文件描述符分配规则体会--重定向 
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    close(1);

    int fd = open("./test.txt", O_CREAT|O_RDWR, 0664);
    if(fd < 0) {
        perror("open error");
        return -1;
    }

    printf("fd:%d\n", fd);
    fflush(stdout);

    close(fd);
    return 0;
}
