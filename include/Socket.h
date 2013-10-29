/*
 * Socket.h
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <boost/noncopyable.hpp>

#include <InetAddress.h>

namespace netlib{
namespace net{

class Socket : boost::noncopyable{
public:
	explicit Socket(int sockfd) : sockfd_(sockfd)
	{

	}

	~Socket(){

	}

	void bindAddress(const InetAddress& peeraddr);
	void listen();
	int accept(InetAddress* peeraddr);

	int fd() const { return sockfd_; }

	void setKeepAlive(bool on);

	void setReusePort(bool on);


private:
	const int sockfd_;

};

}
}



#endif /* SOCKET_H_ */
