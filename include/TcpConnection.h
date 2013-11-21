/*
 * TcpConnection.h
 *
 *  Created on: Sep 24, 2013
 *      Author: lvanlv
 */

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_

#include <boost/scoped_ptr.hpp>

#include <Channel.h>
#include <CallBacks.h>

namespace netlib{
namespace net{

class EventLoop;

class TcpConnection{
public:
	TcpConnection(EventLoop *loop, int sockfd);
	~TcpConnection();

	void setConnectionCallback(const ConnectionCallback& cb)
	{
		connectionCb_ = cb;
	}

	void setCloseCallback(const CloseCallback& cb)
	{
		closeCb_ = cb;
	}

	void setMessageCallback(const MessageCallback& cb)
	{
		messageCb_ = cb;
	}

	void setWriteCompleteedCallback(const WriteCompleteCallback& cb)
	{
		writeCompletedCb_ = cb;
	}

private:
	void readHandle();
	void writeHandle();
	void closeHanle();
	void errorHandle();

private:
	boost::scoped_ptr<Channel> channelPtr_;

	ConnectionCallback connectionCb_;
	CloseCallback closeCb_;
	MessageCallback messageCb_;
	WriteCompleteCallback writeCompletedCb_;

	char* inputBuffer;

};

}}

#endif /* TCPCONNECTION_H_ */
