/*
 * TcpServer.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: lvanlv
 */

#include <boost/bind.hpp>

#include <TcpServer.h>
#include <Acceptor.h>
#include <TcpConnection.h>
#include <EventLoop.h>

namespace netlib{
namespace net{

TcpServer::TcpServer(EventLoop *loop, const InetAddress& listenAddr, const std::string& serverName)
	: started_(false),
	  serverName_(serverName),
	  loop_(loop),
	  acceptor_(new Acceptor(loop, listenAddr)),
	  threadPool_(new EventLoopThreadPool(loop)),
	  connectionCb_(defaultConnectionCallback),
	  messageCb_(defaultMessageCallback)
{
	acceptor_->setNewConnectedCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
}

void TcpServer::setThreadNum(int threadNum)
{
	assert(0 <= threadNum);
	threadPool_->setThreadNum(threadNum);
}

void TcpServer::start()
{
	if(!started_)
	{
		started_ = true;
	}

	if(!acceptor_->isListening())
	{
		acceptor_->listen();
	}


}

void TcpServer::newConnection(int sockfd, const InetAddress& clientAddr)
{
	//TcpConnectionPtr conn(new TcpConnection()); //TODO not finish  it's important
	loop_->assertInLoopThread(); // 暂时不明白意图
	EventLoop *ioLoop = threadPool_->getNextLoop();

	char buf[32];

	TcpConnectionPtr pconn(new TcpConnection(ioLoop, sockfd));
	pconn->setConnectionCallback(connectionCb_);
	pconn->setMessageCallback(messageCb_);
	pconn->setWriteCompleteedCallback(writeCompleteCb_);
	pconn->setCloseCallback(boost::bind(&TcpServer::removeConnection, this, _1));

	ioLoop->runInLoop();
}

void TcpServer::removeConnection(const TcpConnectionPtr& pconn)
{
//	loop_->runInLoop()
}

}}

