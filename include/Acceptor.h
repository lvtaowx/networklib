/*
 * Acceptor.h
 *
 *  Created on: Sep 23, 2013
 *      Author: lvanlv
 */

#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <boost/function.hpp>

#include <Socket.h>
#include <Channel.h>

namespace netlib{
namespace net{

class Acceptor{
public:
	typedef boost::function<void (int sockfd, const InetAddress& )> NewConnectedCallBack;

	Acceptor(EventLoop *loop, const InetAddress& listenAddr);
	~Acceptor();
	void listen();
	void readHandle();

	bool isListening() const {return listening_;}

	void setNewConnectedCallback(const NewConnectedCallBack& cb)
	{
		newConnectedCallBack_ = cb;
	}


private:
	Socket acceptSocket_;
	Channel acceptChannel_;
	bool listening_;

	NewConnectedCallBack newConnectedCallBack_;
};


}
}

#endif /* ACCEPTOR_H_ */
