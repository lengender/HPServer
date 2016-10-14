/*************************************************************************
	> File Name: 11.4.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月26日 星期一 13时25分19秒
 ************************************************************************/

#define TIMEOUT 5000

int timeout = TIMEOUT;
time_t start = time(NULL);
time_t end = time(NULL);

while(1)
{
    printf("the timeout is now %d mil-seconds\n", timeout);
    start = time(NULL);
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, timeout);
    if((number < 0) && (errno != EINTR))
    {
        printf("epoll failure\n");
        :w break;
    }

    //如果epoll_wait成功返回０，则说明超时函数到，此时便可处理定时任务，并重置定时
    //时间
    if(number == 0)
    {
        timeout = TIMEOUT;
        continue;
    }

    end = time(NULL);
    //如果ｅpoll_wait的返回值大于０，则本次epoll_wait调用持续的时间是(end - start)*1000ms
    //我们需要将定时时间timeout减去这段时间，以获得下次epoll_wait调用的超时参数
    timeout -= (end - start) * 1000;
    //超时重新计算之后的timeout值可能等于０，说明本次epoll_wait调用返回时，不仅有
    //文件描述符就绪，而且器超时时间也刚好到达，此时我们也处理定时任务，并重置定时时间
    if(timeout <= 0)
    {
        timeout = TIMEOUT;
    }

    //handle connections
}
