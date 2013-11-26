/*
 * Buffer.h
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <CommonHeadFile.h>

namespace netlib{
namespace net{

/*
 * input and output buffer
 */
class Buffer{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize = 1024;

public:
	Buffer()
		: buffer_( kCheapPrepend + kInitialSize ),
		  readIndex_(kCheapPrepend),
		  writeIndex_(kCheapPrepend)
	{

	}

	size_t readableBytes() const
	{
		return writeIndex_ - readIndex_;
	}

	size_t writeableBytes() const
	{
		return buffer_.size() - writeIndex_;
	}

	size_t prependableBytes() const
	{
		return readIndex_;
	}

	void retrieve(size_t len)
	{

	}

	void retrieveAll()
	{

	}

	std::string retrieveAllToString()
	{

	}

	ssize_t readFd(int fd);

private:
	std::vector<char> buffer_;
	size_t readIndex_;
	size_t writeIndex_;
};

}}

#endif /* BUFFER_H_ */
