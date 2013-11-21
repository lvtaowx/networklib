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
	  inputBuffer(new char[MAXSIZE]),
	  loop_(loop)
{
	channelPtr_->setReadCallBack(boost::bind(&TcpConnection::readHandle, this));
	channelPtr_->setWriteCallBack(boost::bind(&TcpConnection::writeHandle, this));
	channelPtr_->setCloseCallBack(boost::bind(&TcpConnection::closeHanle, this));
}

TcpConnection::~TcpConnection()
{
	if(inputBuffer)
	{
		delete inputBuffer;
		inputBuffer = NULL;
	}
}

void TcpConnection::send(const char* msg)
{
	if(state_ == kConnectioned)
	{
		if(loop_->isInLoopThread())
		{

		}
		else
		{

		}
	}
}

void TcpConnection::readHandle()
{
	socketAct::read(channelPtr_->fd(), (void *)inputBuffer, MAXSIZE);
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



