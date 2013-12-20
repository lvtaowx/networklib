/*
 * SocketsAct.cpp
 *
 *  Created on: Jun 21, 2013
 *      Author: lvanlv
 */

#include <CommonHeadFile.h>

#include <sys/socket.h>
#include <unistd.h>

#include <SocketAct.h>

namespace netlib{
namespace net{

int socketAct::createSockfd(SOCKOPTS flag)
{

	int socketfd;

	switch(flag){
		case sock_stream :
			socketfd = ::socket(AF_INET, SOCK_STREAM  | SOCK_NONBLOCK  | SOCK_CLOEXEC, IPPROTO_TCP);
			break;
		case sock_dgram:
			socketfd = ::socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
			break;
		case sock_packet:
			socketfd = ::socket(AF_INET, SOCK_PACKET | SOCK_NONBLOCK | SOCK_CLOEXEC, htons(0x0003));
			break;
		case sock_raw:
			socketfd = ::socket(AF_INET, SOCK_RAW | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_RAW);
			break;
		default:
			break;
	}

	if(socketfd < 0){
		printf(" create socket failed!\n");
		return -1;
	}

	return socketfd;
}

int socketAct::connect(int sockfd, const struct sockaddr_in& addr)
{

	int error = ::connect(sockfd, (struct sockaddr *)(&addr), static_cast<socklen_t>(sizeof addr));
    if (error < 0) {
         printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
         perror(strerror(errno));
         return -1;
    }

    return error;
}

int socketAct::bind(int sockfd, const struct sockaddr_in& addr)
{

	int error = ::bind(sockfd, (struct sockaddr *)(&addr), static_cast<socklen_t>(sizeof addr));
    if (error < 0) {
         printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
         perror(strerror(errno));
         return -1;
    }

	return 0;
}

int socketAct::listen(int sockfd)
{

	int error = ::listen(sockfd, SOMAXCONN);
    if (error < 0) {
         printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
         perror(strerror(errno));
         return -1;
    }

	return 0;
}

int socketAct::listen(int sockfd, int len)
{
	int error = ::listen(sockfd, len);
    if (error < 0) {
         printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
         perror(strerror(errno));
         return -1;
    }

	return 0;
}

int socketAct::accept(int sockfd, struct sockaddr_in& addr)
{

	socklen_t len = static_cast<socklen_t>(sizeof(addr));
	int connfd = ::accept(sockfd, (struct sockaddr *)(&addr), &len);
	if(connfd < 0){
//		printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
//		perror(strerror(errno));
	}

	return connfd;
}

ssize_t socketAct::read(int sockfd, void *buf, size_t count)
{
	return ::read(sockfd, buf, count);
}

ssize_t socketAct::readv(int sockfd, const struct iovec *iov, int iocnt)
{
	return ::readv(sockfd, iov, iocnt);
}

ssize_t socketAct::write(int sockfd, void *buf, size_t count)
{
	return ::write(sockfd, buf, count);
}

void socketAct::close(int sockfd)
{
	if(::close(sockfd) < 0)
	{
		printf("sockfd close!  %s   %s \n", __FILE__, __FUNCTION__);
	}
}

void socketAct::setNonBlockFd()
{

}

}
}


