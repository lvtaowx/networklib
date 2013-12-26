/*
 * channel.h
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

//#include <EventLoop.h>

namespace netlib{
namespace net{

class EventLoop;

class Channel : boost::noncopyable {
public:
	typedef boost::function<void()> EventCallBack;
	//typedef boost::function<void()> ReadEventCallBack;

	Channel(EventLoop *loop, int fd);

	~Channel()
	{

	}

	int events() const { return events_; }
	int fd() const { return fd_; }
	int index() const { return index_;}

	void set_revents(int revents){ revents_ = revents; }
	void set_index(int idx) { index_ = idx;}
	bool isNoneEvent() const { return events_ == kNoneEvent; }
	EventLoop* ownerLoop() const { return loop_; }

	void handleEvent();

	void setReadCallBack(const EventCallBack& cb)
	{
		readCallBack_ = cb;
	}
	void setWriteCallBack(const EventCallBack& cb)
	{
		writeCallBack_ = cb;
	}
	void setCloseCallBack(const EventCallBack& cb)
	{
		closeCallBack_ = cb;
	}

	void enableReading();
	void enableWriting();
	void disableWriting();
	void disableAll();

	void remove();

private:
	void update();

private:
	const int fd_;
	EventLoop *loop_;
	int events_;
	int index_;
	int revents_; //根据返回的revents来判断是什么事件

	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventCallBack readCallBack_;
	EventCallBack writeCallBack_;
	EventCallBack closeCallBack_;
};

}
}



#endif /* CHANNEL_H_ */
