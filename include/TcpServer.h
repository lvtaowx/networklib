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

namespace netlib{
namespace net{

class Acceptor;
class EventLoop;

class TcpServer{
public:
	typedef boost::function<void (EventLoop*)> ThreadInitCallBack;

public:
	TcpServer(EventLoop *loop, const InetAddress& listenAddr, const std::string& serverName);

	void start();
	void setThreadNum(int threadNum);

	void newConnection(int sockfd, const InetAddress& clientAddr);
	void removeConnection(const TcpConnectionPtr& pconn);

private:


private:
	typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;

	int threadNum_;
	bool started_;
	const std::string serverName_;
	EventLoop *loop_;
	boost::scoped_ptr<Acceptor> acceptor_;
	boost::scoped_ptr<EventLoopThreadPool> threadPool_;
	ConnectionCallback connectioncb_;
	MessageCallback messagecb_;
	WriteCompleteCallback writeCompletecb_;
	ThreadInitCallBack threadInitcb_;
	ConnectionMap connections_;
};

}
}

#endif /* TCPSERVER_H_ */
