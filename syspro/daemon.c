/*************************************************************************
	> File Name: daemon.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年05月10日 星期二 00时11分03秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
int main(void)
{
    int pid;
    pid = fork();
    if(pid >0)
    {
        exit(0);
    }
    if(pid == 0)
    {
        printf("%d\n",getpid());
    }
    setsid();
    chdir("/");
    for(int i = 0; i < 3; i++)
    close(i);
    
    open("/dev/null",O_RDWR);
    dup(0);
    dup(0);

    
}
