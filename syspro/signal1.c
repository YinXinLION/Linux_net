/*************************************************************************
	> File Name: signal1.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年05月10日 星期二 23时14分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<signal.h>

void hander(int num)
{
    printf("recv num: %d\n",num);
    if(num == SIGQUIT)
    {
       exit(0);
    }
}

int main(void)
{
    signal(SIGINT, hander);
    signal(SIGQUIT, hander);
    while(1)
    {
        pause();
    }
    printf("main .. begin\n");
}

