/*************************************************************************
	> File Name: wait1.c
	> Author:YinXin 
	> Mail:www.yinxin19950816@gmail.com 
	> Created Time: 2016年05月10日 星期二 10时24分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>
//检测子进程退出
int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    perror("fork");

    if(pid == 0)
    {
        printf("this is child %d\n",getpid());
        exit(100);
        //abort(); //非正常退出
    }

    int status;
    int ret = wait(&status);//wait 返回子进程pid
    printf("this is parent\n");
    printf("ret = %d, pid = %d \n", ret, getpid());
   
    if(WIFEXITED(status))//正常退出执行
    {
        printf("exit id %d\n",WEXITSTATUS(status));//子进程退出状态为100
    }
    else if(WIFSIGNALED(status))
    {
        printf("err exit id %d\n",WTERMSIG(status));

    }
    else if(WIFSTOPPED(status))
    {
        printf("stop id %d\n",WSTOPSIG(status));
    }
    else
    {
        printf("other exit\n");
    }











}
