/*
 * Buffer.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#include <sys/uio.h>

#include <Buffer.h>
#include <SocketAct.h>

namespace netlib{
namespace net{

ssize_t Buffer::readFd(int fd)
{
	char extrabuf[65536];// 用来保存buffer_中放不下的数据 详见<<linux多线程服务端编程>>
	struct iovec vec[2];
	const size_t writeable = writeableBytes();
	vec[0].iov_base = begin() + writeIndex_;
	vec[0].iov_len = writeable;
	vec[1].iov_base = extrabuf;
	vec[1].iov_len = sizeof(extrabuf);

	const ssize_t n = socketAct::readv(fd, vec, 2);
	if(n <= 0)
	{

	}

}

}}


