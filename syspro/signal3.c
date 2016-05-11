/*************************************************************************
	> File Name: signal3.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年05月11日 星期三 22时55分20秒
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

void handler(int num)
{
    printf("recv num: %d \n",num);
    if(num == SIGQUIT)
    exit(0);
}

int main(void)
{
    char tmpchar;

    signal(SIGINT, handler);
    printf("if input a defalt signal\n");
    while((tmpchar = getchar()) != 'a')
    {
        pause();
    }
    
    signal(SIGINT, SIG_DFL);//让信号恢复默认状态

    while(1)
    {
        pause();
    }
    printf("END\n");
}
