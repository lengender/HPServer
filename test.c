/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月20日 星期二 16时13分33秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main()
{

    int a[10];

    memset(a, 2, sizeof(a));

    int i;
    for(i = 0; i < 10; ++i)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
