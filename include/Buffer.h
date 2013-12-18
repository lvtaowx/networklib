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

/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode


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
		assert(readableBytes() == 0);
		assert(writeableBytes() == kInitialSize);
		assert(prependableBytes() == kCheapPrepend);
	}

	void swap(Buffer& rhs)
	{
		buffer_.swap(rhs.buffer_);
		std::swap(readIndex_, rhs.readIndex_);
		std::swap(writeIndex_, rhs.writeIndex_);
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

	const char* peek() const
	{
		return begin() + readIndex_;
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

	std::string retrieveAsString()
	{

	}

	char* beginWrite()
	{
		return begin()+writeIndex_;
	}

	void hasWriten(size_t len)
	{
		writeIndex_ += len;
	}

	ssize_t readFd(int fd);

private:
	char* begin()
	{
		return (&*buffer_.begin());
	}

	const char* begin() const
	{
		return (&*buffer_.begin());
	}

private:
	std::vector<char> buffer_;
	size_t readIndex_;
	size_t writeIndex_;
};

}}

#endif /* BUFFER_H_ */
