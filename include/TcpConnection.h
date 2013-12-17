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
#include <Buffer.h>

namespace netlib{
namespace net{

class EventLoop;

/*
 *  每个fTcpConnection 都绑定了自己的 channel
 */

class TcpConnection{
	enum State{ kDisconnected, kConnected, kConnecting, kDisconnecting };
public:
	TcpConnection(EventLoop *loop, int sockfd);
	~TcpConnection();

	void send(const char* msg);

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

	void connectionEstablished();

private:
	void readHandle();
	void writeHandle();
	void closeHanle();
	void errorHandle();
	void setState(State s)
	{
		state_ = s;
	}

private:
	boost::scoped_ptr<Channel> channelPtr_;

	ConnectionCallback connectionCb_;
	CloseCallback closeCb_;
	MessageCallback messageCb_;
	WriteCompleteCallback writeCompletedCb_;

	State state_;
	Buffer inputBuffer;
	Buffer outputBuffer;
	EventLoop* loop_;

};

}}

#endif /* TCPCONNECTION_H_ */
