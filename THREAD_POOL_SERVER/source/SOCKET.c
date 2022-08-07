#include <SOCKET.h>

int SOCKET(int domain,int type,int protocol)
{
	int sockfd;
	if((sockfd = socket(domain,type,protocol))==-1){
		perror("socket create failed.");
	}
	return sockfd;
}

int BIND(int sockfd,const struct sockaddr * addr,socklen_t addrlen)
{
	int reval;
	if((reval = bind(sockfd,addr,addrlen))==-1){
		perror("bind call failed.");
	}
	return reval;
}

int LISTEN(int sockfd,int backlog)
{
	int reval;
	if((reval = listen(sockfd,backlog))==-1){
		perror("listen call failed.");
	}
	return reval;
}

int CONNECT(int sockfd,const struct sockaddr *addr,socklen_t addrlen)
{
	int reval;
	if((reval = connect(sockfd,addr,addrlen))==-1){
		perror("connect call failed.");
	}
	return reval;
}

int ACCEPT(int sockfd,struct sockaddr * addr,socklen_t * addrlen)
{
	int clientfd;
	if((clientfd = accept(sockfd,addr,addrlen))==-1){
		perror("accept call failed.");
	}
	return clientfd;
}

ssize_t RECV(int sockfd,void *buf,size_t len,int flags)
{
	ssize_t recvlen;
	if((recvlen = recv(sockfd,buf,len,flags))==-1){
		if(errno == EAGAIN){
			return recvlen;
		}
		else{
			perror("recv call failed.");
		}
	}
	return recvlen;
}

ssize_t SEND(int sockfd,const void *buf,size_t len,int flags)
{
	ssize_t sendlen;
	if((sendlen = send(sockfd,buf,len,flags))==-1){
		perror("send call failed.");
	}
	return sendlen;
}
