/*
 * InetAddress.cpp
 *
 *  Created on: Aug 30, 2013
 *      Author: lvanlv
 */

#include <InetAddress.h>
#include <string.h>  //bzero 的头文件
#include <arpa/inet.h>

namespace netlib{
namespace net{

InetAddress::InetAddress(int port)
{
	bzero(&addr_, sizeof(addr_));

	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
//	if (::inet_pton(AF_INET, ip, &addr.sin_addr) <= 0)
//	{
//	   printf( "sockets::fromIpPort");
//	}


}

InetAddress::InetAddress(std::string ip, int port)
{
	bzero(&addr_, sizeof(addr_));

	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);
	addr_.sin_addr.s_addr = inet_addr(ip.c_str());
//	if (::inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr) <= 0)
//	{
//	   printf( "sockets::fromIpPort");
//	}

}

void InetAddress::setSockAddrInet(const sockaddr_in& addr)
{
	addr_ = addr;
}

std::string InetAddress::toIpPort() const
{
	std::string str;
	return str;
}

}
}


