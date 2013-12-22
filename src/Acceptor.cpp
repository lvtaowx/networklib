/*
 * Acceptor.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: lvanlv
 */

#include <boost/bind.hpp>

#include <Acceptor.h>
#include <SocketAct.h>

namespace netlib{
namespace net{

Acceptor::Acceptor(EventLoop *loop, const InetAddress& listenAddr)
		: acceptSocket_(socketAct::createSockfd()),
		  acceptChannel_(loop, acceptSocket_.fd()),
		  listening_(false)
{
	acceptSocket_.bindAddress(listenAddr);
	acceptChannel_.setReadCallBack(boost::bind(&Acceptor::readHandle, this));
}

Acceptor::~Acceptor()
{
	acceptChannel_.disableAll();
	acceptChannel_.remove();
}

void Acceptor::listen()
{
	acceptSocket_.listen();
	listening_ = true;
	acceptChannel_.enableReading();
}

void Acceptor::readHandle()
{
	InetAddress clientAddr(0);
	int connfd = acceptSocket_.accept(&clientAddr);

	if(connfd >= 0)
	{
		if(newConnectedCallBack_)
		{
			newConnectedCallBack_(connfd, clientAddr);
		}
		else
		{
			socketAct::close(connfd);
		}
	}
	else
	{
		//TODO
	}

}


}
}

