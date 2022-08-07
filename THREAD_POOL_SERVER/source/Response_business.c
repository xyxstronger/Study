#include <THREAD_POOL_SERVER.h>
#include <SOCKET.h>

void * Response_busines(void * arg)
{

	int clientfd = *(int *)arg;

	//交互变量
	char buf[_BUFSIZE];
	ssize_t recvlen;
	int flag; //转换下标
	char time_buf[1024];
	time_t t;
	bzero(buf,sizeof(buf));
	bzero(time_buf,sizeof(time_buf));

	while((recvlen = RECV(clientfd,buf,sizeof(buf),MSG_DONTWAIT))>0){

		if(strcmp(buf,"timeofday\n")==0){
			t = time(NULL);
			ctime_r(&t,time_buf);
			//response
			SEND(clientfd,time_buf,strlen(time_buf),MSG_DONTWAIT);
			bzero(buf,sizeof(buf));
			bzero(time_buf,sizeof(time_buf));
		}
		else{
			flag = 0;
			while(recvlen > flag){
				buf[flag] = toupper(buf[flag]);
				flag++;
			}
			SEND(clientfd,buf,strlen(buf),MSG_DONTWAIT);
			bzero(buf,sizeof(buf));
		}   
	}
	if(recvlen == 0){ 
		printf("Customer thread <0x%x> Response data success...\n",(unsigned int)pthread_self());
		epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,NULL);
		close(clientfd);
	}

	return NULL;
}
