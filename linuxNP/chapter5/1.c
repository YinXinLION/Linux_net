/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月22日 星期五 09时52分32秒
 ************************************************************************/

#include<stdio.h>

void byteorder()
{
    union
    {
        short value;
        char union_bytes[sizeof(short)];
    }test;

    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    printf("big endian\n");
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    printf("little endian\n");
    else
    printf("unknown..\n");
}

int main(void)
{
    byteorder();
    return 0;
}
