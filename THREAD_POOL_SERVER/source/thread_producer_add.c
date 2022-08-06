#include <THREAD_POOL_SERVER.h>

int thread_producer_add(thread_pool_t * p,task_t task)
{
	if(p->thread_shutdown){
		pthread_mutex_lock(&p->lock);
		//当任务队列为满，挂起生产者线程
		while(p->queue_cur == p->queue_max){
			pthread_cond_wait(&p->not_full,&p->lock);
		}
		if(!p->thread_shutdown){
			pthread_mutex_unlock(&p->lock);
			pthread_exit(NULL);
		}
		//向任务容器中添加任务
		p->task_list[p->queue_front].work = task.work;
		p->task_list[p->queue_front].arg = task.arg;
		(p->queue_cur)++;
		p->queue_front = (p->queue_front + 1) % p->queue_max;
		printf(">>>>> producer thread tid <0x%x> add task success!\n",(unsigned int)pthread_self());
		pthread_mutex_unlock(&p->lock);
		pthread_cond_signal(&p->not_empty);
	}
	return 0;
}
