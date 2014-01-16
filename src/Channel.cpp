/*
 * channel.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#include <poll.h>

#include <Channel.h>
#include <EventLoop.h>

namespace netlib{
namespace net{

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI; //POLLPRI 有紧急数据可读
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop, int fd)
	: fd_(fd),
	  loop_(loop),
	  events_(0),
	  revents_(0),
	  index_(-1)
{

}

void Channel::handleEvent() //如果是 poll来实现底层的话 则会返回 POLLNVAL 等事件
{
	if((revents_ & POLLHUP) && !(revents_ & POLLIN))
	{
		if(closeCallBack_) closeCallBack_();
	}

	if(revents_ & (POLLIN | POLLPRI | POLLRDHUP))
	{
		if(readCallBack_) readCallBack_();
	}

	if(revents_ & (POLLERR | POLLNVAL))
	{
		if(errorCallBack_) errorCallBack_();
	}

	if(revents_ & POLLOUT)
	{
		if(writeCallBack_) writeCallBack_();
	}

}

void Channel::enableReading()
{
	events_ |= kReadEvent;
	update();
}

void Channel::enableWriting()
{
	events_ |= kWriteEvent;
	update();
}

void Channel::disableWriting()
{
	events_ &= -kWriteEvent;
	update();
}

void Channel::disableAll()
{
	events_ &= kNoneEvent;
	update();
}

void Channel::remove()
{
	assert( isNoneEvent() );
	loop_->removeChannel(this);
}

void Channel::update()
{
	loop_->updateChannel(this);
}

}
}

