/*
 * InetAddress.h
 *
 *  Created on: Aug 30, 2013
 *      Author: lvanlv
 */

#ifndef INETADDRESS_H_
#define INETADDRESS_H_

#include <CommonHeadFile.h>

#include <netinet/in.h> //套接口地址结构的头文件

namespace netlib{
namespace net{

class InetAddress{
public:
	explicit InetAddress(int port); //不可用 TODO
	InetAddress(std::string ip, int port);

	const struct sockaddr_in& getNetAddress() const {return addr_;}
	void setSockAddrInet(const struct sockaddr_in& addr);

private:
	struct sockaddr_in addr_;
};

}
}



#endif /* INETADDRESS_H_ */
