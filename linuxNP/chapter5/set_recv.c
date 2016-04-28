/*************************************************************************
	> File Name: set_recv.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年04月28日 星期四 17时20分39秒
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
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage: %s ip_address prot_number recv_buffer_size\n",basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int recvbuf = atoi(argv[3]);
    int len = sizeof(recvbuf);
    //先设置接收大小，再读取
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, len);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *)&len);
    
    printf("the tcp receive buffer size after setting is %d\n",recvbuf);
    
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);
    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;

    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct  sockaddr *)&client, &client_addrlength);
    if(connfd < 0)
    {
        printf("errno is : %d\n",errno);
    }
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer,0,BUFFER_SIZE);
        while(recv(connfd, buffer, BUFFER_SIZE - 1, 0) > 0)
        {
            
        }
        close(connfd);
    }
    close(sock);
    return 0;
}
