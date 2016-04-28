/*************************************************************************
	> File Name: 4.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年04月28日 星期四 16时37分01秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<assert.h>
#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage: %s ip_address port_number send_bufer_size\n",basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int sendbuf = atoi(argv[3]); //缓冲区大小
    int len = sizeof(sendbuf);
    //先设置TCP发送缓冲区的大小，然后立即读取之，
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&len);
    printf("the tcp send buffer size after setting is %d\n",sendbuf);

    if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) != -1)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, 'a', BUFFER_SIZE);
        send(sock, buffer, BUFFER_SIZE, 0);
    }
    close(sock);
    return 0;
}
