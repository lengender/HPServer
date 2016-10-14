/*************************************************************************
	> File Name: event_add_internal.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月27日 星期二 21时01分05秒
 ************************************************************************/

static inline int event_add_internal(struct event *ev,
                                    const struct timeval *tv,
                                    int tv_is_absolute)
{
    struct event_base *base = ev->event_base;
    int res = 0;
    int notify = 0;

    EVENT_BASE_ASSERT_LOCKED(base);
    _event_debug_assert_is_setup(ev);

    event_debug((
        "event_add: event: %p (fd %d), %s%s%scall %p",
        ev,
        (int)ev->ev_fd,
        ev->ev_events & EV_READ ? "EV_READ " : " ",
        ev->ev_events & EV_WRITE ? "EV_WRITE " : " ",
        tv ? "EV_TIMEOUT " : " ",
        ev->ev_callback));

    EVTIL_ASSERT(!(ev->ev_flags & ~EVLIST_ALL));

    //如果新添加的事件处理器是定时器，且它尚未被添加到通用定时器队列或时间堆中，
    //则为该定时器在时间堆上预留一个位置
    if(tv != NULL && !(ev->ev_flags & EVLIST_TIMEOUT))
    {
        if(min_heap_reverse(&base->timeheap,
                           1 + min_heap_size(&base->timeheap)) == -1)
            return -1;
    }
}
