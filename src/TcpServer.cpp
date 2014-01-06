/*
 * TcpServer.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: lvanlv
 */

#include <boost/bind.hpp>

#include <TcpServer.h>
#include <Acceptor.h>
#include <EventLoop.h>
#include <EventLoopThreadPool.h>

namespace netlib{
namespace net{

TcpServer::TcpServer(EventLoop *loop, const InetAddress& listenAddr, const std::string& serverName)
	: started_(false),
	  serverName_(serverName),
	  hostPort_(listenAddr.toIpPort()),
	  baseLoop_(loop),
	  acceptor_(new Acceptor(baseLoop_, listenAddr)),
	  threadPool_(new EventLoopThreadPool(baseLoop_)),
	  connectionCb_(defaultConnectionCallback),
	  messageCb_(defaultMessageCallback),
	  nextConnnID(1)
{
	acceptor_->setNewConnectedCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer()
{
	printf("this is %s  %s  %d\n", __FILE__, __FUNCTION__, __LINE__);
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
		threadPool_->start(threadInitcb_);
	}

	if(!acceptor_->isListening())
	{
		baseLoop_->runInLoop(boost::bind(&Acceptor::listen, get_pointer(acceptor_)));
//		acceptor_->listen();//在创建acceptor的时候 初始化并且bind了 socket
	}
}

void TcpServer::newConnection(int sockfd, const InetAddress& clientAddr)
{
	//TcpConnectionPtr conn(new TcpConnection()); //TODO not finish  it's important
	baseLoop_->assertInLoopThread(); // 暂时不明白意图
	EventLoop *ioLoop = threadPool_->getNextLoop();

	++nextConnnID;
	std::string connName;
	char buf[32];
	snprintf(buf, sizeof buf, ":%s#%d", hostPort_.c_str(), nextConnnID);
	connName = serverName_ + buf;

	TcpConnectionPtr pconn(new TcpConnection(ioLoop, sockfd));
	connections_[connName] = pconn;

	pconn->setConnectionCallback(connectionCb_);
	pconn->setMessageCallback(messageCb_);
	pconn->setWriteCompleteedCallback(writeCompleteCb_);
	pconn->setCloseCallback(boost::bind(&TcpServer::removeConnection, this, _1));

	ioLoop->runInLoop(boost::bind(&TcpConnection::connectionEstablished, pconn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& pconn)
{
//TODO
//	loop_->runInLoop()
}

}}

