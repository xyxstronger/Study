#include <THREAD_POOL_SERVER.h>

thread_pool_t * thread_pool_create(int tmax,int tmin,int qmax)
{
	//线程池空间申请
	thread_pool_t * p = NULL;
	if((p = (thread_pool_t*)malloc(sizeof(thread_pool_t)))==NULL){
		thread_pool_error("thread_pool_create call failed, malloc thread_pool_t error",-1,0);
	}

	//阈值设置初始值
	p->thread_max = tmax;
	p->thread_min = tmin;
	p->thread_alive = 0;
	p->thread_busy = 0;
	p->thread_shutdown = TRUE;
	p->thread_exitcode = 0;

	//申请任务队列空间
	if((p->task_list = (task_t*)malloc(sizeof(task_t)*qmax))==NULL){
		thread_pool_error("thread_pool_create call failed, malloc task_list error",-1,0);
	}
	//任务队列赋值
	p->queue_front = 0;
	p->queue_rear = 0;
	p->queue_cur = 0;
	p->queue_max = qmax;

	//消费者线程空间申请
	if((p->customer_tids = (pthread_t*)malloc(sizeof(pthread_t)*tmax))==NULL){
		thread_pool_error("thread_pool_create call failed, malloc customer_tids error",-1,0);
	}
	//初始化
	bzero(p->customer_tids,sizeof(pthread_t)*tmax);

	//初始化锁和条件变量
	if(pthread_mutex_init(&p->lock,NULL)!=0 || pthread_cond_init(&p->not_full,NULL)!=0 || pthread_cond_init(&p->not_empty,NULL)!=0){
		thread_pool_error("thread_pool_create call failed, init lock or cond error",-1,0);
	}

	//管理者线程创建
	int err;
	if((err = pthread_create(&p->manager_tid,NULL,thread_manager,(void *)p))>0){	
		thread_pool_error("thread_pool_create call failed, create manager error",-1,err);
	}

	//消费者线程创建
	for(int i=0;i<tmin;i++){
		if((err = pthread_create(&p->customer_tids[i],NULL,thread_customer,(void *)p))>0){	
			thread_pool_error("thread_pool_create call failed, create customer error",-1,err);
		}
		++(p->thread_alive);
	}
	
	return p;
}
