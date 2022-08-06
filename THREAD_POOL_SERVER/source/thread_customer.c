#include <THREAD_POOL_SERVER.h>

void * thread_customer(void *arg)
{
	thread_pool_t * p = (thread_pool_t *)arg;
	task_t tmptask;

	while(p->thread_shutdown){
		pthread_mutex_lock(&p->lock);
		//当任务队列中任务数为0
		while(p->queue_cur == 0){
			pthread_cond_wait(&p->not_empty,&p->lock);
			if(p->thread_exitcode > 0){
				--(p->thread_exitcode);
				--(p->thread_alive);
				pthread_mutex_unlock(&p->lock);
				pthread_exit(NULL);
			}
		}
		if(!p->thread_shutdown){
			--(p->thread_alive);
			pthread_mutex_unlock(&p->lock);
			pthread_exit(NULL);
		}
		//获取任务
		tmptask.work = p->task_list[p->queue_rear].work;
		tmptask.arg = p->task_list[p->queue_rear].arg;
		--(p->queue_cur);
		p->queue_rear = (p->queue_rear + 1) % p->queue_max;
		++(p->thread_busy);
		printf(">>>>> customer thread tid <0x%x> get work success!\n",(unsigned int)pthread_self());
		pthread_mutex_unlock(&p->lock);
		pthread_cond_signal(&p->not_full);
		//执行任务
		(tmptask.work)(tmptask.arg);
		//将忙线程数--
		pthread_mutex_lock(&p->lock);
		--(p->thread_busy);
		pthread_mutex_unlock(&p->lock);
	}
	pthread_exit(NULL);
}
