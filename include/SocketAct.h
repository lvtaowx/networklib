/*
 * SocketsAct.h
 *
 *  Created on: Jun 21, 2013
 *      Author: lvanlv
 */

#ifndef SOCKETSACT_H_
#define SOCKETSACT_H_

#include <arpa/inet.h>

namespace netlib{
namespace net{

namespace socketAct{

typedef enum sockopts{
	sock_raw,
	sock_packet,
	sock_stream,
	sock_dgram,
} SOCKOPTS;

// flag is indicate whether or not to set the socketfd blocking or nonblocking
// return socketfd
int createSockfd(SOCKOPTS flag = sock_stream);

int connect(int sockfd, const struct sockaddr_in& addr);

int bind(int sockfd, const struct sockaddr_in& addr);

int listen(int sockfd);
int listen(int sockfd, int len);

int accept(int sockfd, struct sockaddr_in& addr); //返回一个链接套接字

ssize_t read(int sockfd, void *buf, size_t count);
ssize_t readv(int sockfd, const struct iovec *iov, int iocnt);

ssize_t write(int sockfd, const void *buf, size_t count);

void close(int sockfd);

void setNonBlockFd();

void toIpPort(char* buf, size_t size,
		const struct sockaddr_in& addr);

void toIp(char* buf, size_t size,
			const struct sockaddr_in& addr);

}

}
}



#endif /* SOCKETSACT_H_ */
