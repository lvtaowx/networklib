/*
 * TcpServer.h
 *
 *  Created on: Jun 24, 2013
 *      Author: lvanlv
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <string>

#include <boost/scoped_ptr.hpp>

#include <InetAddress.h>
#include <CallBacks.h>
#include <EventLoopThreadPool.h>
#include <Acceptor.h>

namespace netlib{
namespace net{

//FIXME 如果是前置声明则 测试程序会报错
//class Acceptor;
class EventLoop;
//class EventLoopThreadPool;

class TcpServer{
public:
	typedef boost::function<void (EventLoop*)> ThreadInitCallback;

public:
	TcpServer(EventLoop *loop, const InetAddress& listenAddr, const std::string& serverName);

	void setThreadNum(int threadNum);
	void setThreadInitCallback(const ThreadInitCallback& cb){} //TODO  i don't know what's the function

	void setConnetionCallback(const ConnectionCallback& cb)
	{
		connectionCb_ = cb;
	}

	void setMessageCallback(const MessageCallback& cb)
	{
		messageCb_ = cb;
	}

	void setWritingCompleteCallback(const WriteCompleteCallback& cb)
	{
		writeCompleteCb_ = cb;
	}

	void start();

private:
	void newConnection(int sockfd, const InetAddress& clientAddr);
	void removeConnection(const TcpConnectionPtr& pconn);

private:
	typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;

	int threadNum_;
	bool started_;
	const std::string serverName_;
	EventLoop *baseLoop_;
	boost::scoped_ptr<Acceptor> acceptor_;
	boost::scoped_ptr<EventLoopThreadPool> threadPool_;
	ConnectionCallback connectionCb_;
	MessageCallback messageCb_;
	WriteCompleteCallback writeCompleteCb_;
	ThreadInitCallback threadInitcb_;
	ConnectionMap connections_;
};

}
}

#endif /* TCPSERVER_H_ */
