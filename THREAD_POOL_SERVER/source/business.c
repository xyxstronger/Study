#include <THREAD_POOL_SERVER.h>

void * business(void * arg)
{
	printf("测试任务...\n");
	sleep(5);
	return NULL;
}
