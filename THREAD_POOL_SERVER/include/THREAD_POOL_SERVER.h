#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

#define _DELCODE 10 //扩容缩减数量
#define _IP "192.168.189.137"
#define _PORT 8080
#define _BACKLOG 128
#define _BUFSIZE 1500
#define _IPSIZE 16
#define _EPOLLSIZE 100000
#define TRUE 1
#define FALSE 0

//任务类型
typedef struct 
{
	void * (*work)(void *);  //业务地址
	void * arg; //业务参数
}task_t;

//线程池类型
typedef struct
{
	//基本阈值
	int thread_max; 	//线程池中线程最大值
	int thread_min; 	//线程池中线程最小值
	int thread_alive; 	//当前存活线程数量
	int thread_busy; 	//当前忙线程数量
	int thread_shutdown; 	//线程开关 1:start 0:stop
	int thread_exitcode; 	//缩减

	//任务容器
	task_t * task_list;  //任务队列地址
	int queue_front; 	//头索引
	int queue_rear;     //尾索引
	int queue_cur;      //队列当前任务数
	int queue_max;      //队列最大任务数

	//线程信息
	pthread_t producer_tid; //生产者线程
	pthread_t manager_tid;  //管理者线程
	pthread_t * customer_tids; //消费者线程

	//锁
	pthread_mutex_t lock;
	pthread_cond_t not_full; //生产者条件变量
	pthread_cond_t not_empty; //消费者条件变量

}thread_pool_t;

//模块
//线程池创建初始化
thread_pool_t * thread_pool_create(int tmax,int tmin,int qmax);
//线程池销毁
int thread_pool_destroy(thread_pool_t * p);
//线程是否存活
int thread_if_alive(pthread_t tid);
//错误处理
int thread_pool_error(const char * strerr,long int exitcode,int flag);
//生产者任务
int thread_producer_add(thread_pool_t * p,task_t task);
//管理者任务
void * thread_manager(void * arg);
//消费者任务
void * thread_customer(void * arg);
//业务实现
void * business(void *);





