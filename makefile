inc=threadpool.h http_conn.h
obj=http_conn.o 15.6.o

%.o : %.c
	g++ -c -o $@ $< 

tpoll : $(obj)
	g++ -w -o tpoll $^ -I . -lpthread
