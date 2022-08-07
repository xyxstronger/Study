#pragma once
#include <THREAD_POOL_SERVER.h>

//网络模块包裹函数

int SOCKET(int,int ,int);
int BIND(int ,const struct sockaddr *,socklen_t);
int LISTEN(int ,int);
int CONNECT(int ,const struct sockaddr * ,socklen_t);
int ACCEPT(int ,struct sockaddr *,socklen_t *);
ssize_t RECV(int ,void *,size_t,int);
ssize_t SEND(int,const void *,size_t,int);
