#include <THREAD_POOL_SERVER.h>

void * thread_manager(void * arg)
{
	thread_pool_t * p = (thread_pool_t *)arg;
	pthread_detach(pthread_self());

	int alive;
	int busy;
	int cur;

	int flags;
	int add;
	int err;

	while(p->thread_shutdown){
		//获取线程池阈值
		pthread_mutex_lock(&p->lock);
		alive = p->thread_alive;
		busy = p->thread_busy;
		cur = p->queue_cur;
		pthread_mutex_unlock(&p->lock);


		if(alive){
			printf(">>>>> Thread_Pool_Info:\n\t\tshutdown:%d\n\t\talive:%d\n\t\tbusy:%d\n\t\tidel:%d\n\t\tcur:%d\n\t\tbusy/alive:%.2f%%\n\t\talive/all:%.2f%%\n",p->thread_shutdown,alive,busy,alive-busy,cur,(double)busy/alive*100,(double)alive/p->thread_max*100);
		}

		//扩容条件
		//当前线程数量 大于 空闲线程数量 或 忙线程 占比大于等于70% ， 扩容后线程数小于线程池容量最大值
		if((cur > alive - busy || busy / alive * 100 >= 70) && alive + _DELCODE <= p->thread_max){
			printf("Manage: 满足扩容条件，执行创建...\n");
			for(flags = 0,add = 0;flags < p->thread_max && add < _DELCODE;flags++){
				if(p->customer_tids[flags] == 0 || !thread_if_alive(p->customer_tids[flags])){
					if((err = pthread_create(&p->customer_tids[flags],NULL,thread_customer,(void *)p))>0){
						thread_pool_error("thread_manager call failed, create thread error",-1,err);
					}
					add++;
					pthread_mutex_lock(&p->lock);
					++(p->thread_alive);
					pthread_mutex_unlock(&p->lock);
				}
			}
		}

		//缩减条件
		if(busy * 2 <= alive - busy && alive - _DELCODE >= p->thread_min){
			printf("Manage: 满足缩减条件，执行销毁...\n");
			//管理者触发缩减，唤醒闲线程，指定缩减数量，消费者线程被唤醒结束自身
			pthread_mutex_lock(&p->lock);
			p->thread_exitcode = _DELCODE;
			pthread_mutex_unlock(&p->lock);

			for(int i = 0;i < _DELCODE;i++){
				pthread_cond_signal(&p->not_empty);
			}
		}

		sleep(2);

	}

	pthread_exit(NULL);
}
