/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月22日 星期五 10时18分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define false 0
#define true 1
static int stop = false;
//SIGTERM信号的处理函数，触发时结束主程序中的循环
static void handle_term(int sig)
{
    stop = true;
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, handle_term);
    if(argc <= 3)
    {
        printf("usage: %s ip_address port_number backlog\n",basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    //创建一个ipv4 socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != 1);

    ret = listen(sock, backlog);
    assert(ret != 1);

    //循环等待连接，知道有SIGTERM信号讲它中断
    while(!stop)
    {
        sleep(1);
    }

    //关闭socket
    close(sock);
    return 0;
}
