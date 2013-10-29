/*
 * Socket.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#include <Socket.h>
#include <SocketAct.h>

namespace netlib{
namespace net{

void Socket::bindAddress(const InetAddress& peeraddr)
{
	socketAct::bind(sockfd_, peeraddr.getNetAddress());
}

void Socket::listen()
{
	socketAct::listen(sockfd_);
}

int Socket::accept(InetAddress* peeraddr)
{
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	int connfd = socketAct::accept(sockfd_, addr);

	if(connfd >= 0)
	{
		peeraddr->setSockAddrInet(addr);
	}

	return connfd;
}

void Socket::setKeepAlive(bool on)
{

	return ;
}

void Socket::setReusePort(bool on){

	return ;
}



}
}

