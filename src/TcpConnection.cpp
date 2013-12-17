/*
 * TcpConnection.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: lvanlv
 */

#include <boost/bind.hpp>

#include <TcpConnection.h>
#include <EventLoop.h>
#include <SocketAct.h>
#include <Buffer.h>

#define MAXSIZE 500

namespace netlib{
namespace net{

void defaultConnectionCallback(const TcpConnectionPtr& conn)
{

}

void defaultMessageCallBack(const TcpConnectionPtr& conn, Buffer* buffer)
{

}

TcpConnection::TcpConnection(EventLoop *loop, int sockfd)
	: channelPtr_(new Channel(loop, sockfd) ),
	  loop_(loop)
{
	channelPtr_->setReadCallBack(boost::bind(&TcpConnection::readHandle, this));
	channelPtr_->setWriteCallBack(boost::bind(&TcpConnection::writeHandle, this));
	channelPtr_->setCloseCallBack(boost::bind(&TcpConnection::closeHanle, this));
}

TcpConnection::~TcpConnection()
{
//	if(inputBuffer)
//	{
//		delete inputBuffer;
//		inputBuffer = NULL;
//	}
}

void TcpConnection::send(const char* msg)
{
	if(state_ == kConnected)
	{
		if(loop_->isInLoopThread())
		{

		}
		else
		{

		}
	}
}

void TcpConnection::connectionEstablished()
{
	loop_->assertInLoopThread();
	assert(state_ == kConnecting);
	setState(kConnected);

	//FIXME
	//channelPtr_->tie();
	channelPtr_->enableReading();

	//FIXME share_from_this;  这里声明是使用了 share_ptr 编译不过
//	connectionCb_(this);
}

void TcpConnection::readHandle()
{
//	socketAct::read(channelPtr_->fd(), (void *)inputBuffer, MAXSIZE); // just to test
	loop_->assertInLoopThread();
	ssize_t n = inputBuffer.readFd(channelPtr_->fd());
	if(n > 0)
	{

	}
	else if(n == 0)
	{

	}
	else
	{

	}
}

void TcpConnection::writeHandle()
{

}

void TcpConnection::closeHanle()
{

}

void TcpConnection::errorHandle()
{

}

}}



