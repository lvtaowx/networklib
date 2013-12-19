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


/*
 * buffer 中的数据用不着清零 因为读写都是有下标控制的，不会读取到上一次的数据
 * prepend 即提供 prependable 空间，让程序能以很低的代价在数据前面添加几个字节。
 *
 *
 */

class Buffer{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize = 1024;

public:
	Buffer()
		: buffer_( kCheapPrepend + kInitialSize ), //初始化vector的大小
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

	void ensureWriteable(size_t len)
	{
		if(writeableBytes() <= len)
		{
			makespace(len);
		}
		else
		{

		}
	}

	void append(const char* data, size_t len)
	{
		ensureWriteable(len);
		std::copy(data, data+len, beginWrite());
		hasWriten(len);
	}

	void append(const void* data, size_t len)
	{
		append(static_cast<const char*>(data), len);
	}

	void retrieve(size_t len)
	{
		assert(len <= readableBytes());
		if(len < readableBytes())
		{
			readIndex_ += len;
		}
		else
		{
			retrieveAll();
		}
	}

	void retrieveAll()
	{
	    readIndex_ = kCheapPrepend;
	    writeIndex_ = kCheapPrepend;
	}

	std::string retrieveAllToString()
	{
		return retrieveAsString(readableBytes());
	}

	std::string retrieveAsString(size_t len)
	{
		assert(len <= readableBytes());
		std::string result(peek() + len);
		//TODO this step is important
		retrieve(len);
		return result;
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

	void makespace(size_t len)
	{
		if(writeableBytes() + prependableBytes() < len + kCheapPrepend)
		{
			buffer_.resize(writeIndex_ + len);
		}
		else
		{
			assert(kCheapPrepend < readIndex_);
			ssize_t readable = readableBytes();
			std::copy(begin() + readIndex_,
					  begin() + writeIndex_,
					  begin() + kCheapPrepend );
			readIndex_ = kCheapPrepend;
			writeIndex_ = readIndex_ + readable;
			//TODO 不太明白这里为什么要这样断言 莫非是多线程的缘故
			assert(readable == readableBytes());
		}
	}

private:
	std::vector<char> buffer_;
	size_t readIndex_;
	size_t writeIndex_;
};

}}

#endif /* BUFFER_H_ */
