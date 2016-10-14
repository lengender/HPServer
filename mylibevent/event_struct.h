/*************************************************************************
	> File Name: event_struct.h
	> Author: 
	> Mail: 
	> Created Time: 2016年09月27日 星期二 20时42分48秒
 ************************************************************************/

#ifndef _EVENT_STRUCT_H
#define _EVENT_STRUCT_H

struct event
{
    TAILQ_ENTRY(evnet) ev_active_next;
    TAILQ_ENTRY(event) ev_next;
    union{
        TAILQ_ENTRY(event) ev_next_with_common_timeout;
        int min_heap_idx;
    }ev_timeout_pos;
    evutil_socket_t ev_fd;

    struct event_base* ev_base;

    union
    {
        struct
        {
            TAILQ_ENTRY(event) ev_io_next;
            struct timeval ev_timeout;
        }ev_io;

        struct 
        {
            TAILEQ_ENTRY(event) ev__signal_next;
            short ev_ncalls;
            short *ev_pncalls;
        }ev_signal;
    }_ev;

    short ev_events;
    short ev_res;
    short ev_flags;
    ev_uint8_t ev_pri;
    ev_uint8_t ev_closure;
    struct timeval ev_timeout;

    void (*ev_callback)(evutil_socket_t, short, void *arg);
    void *ev_arg;
};
#endif
