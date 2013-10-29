/*
 * EventLoopThread.h
 *
 *  Created on: Aug 30, 2013
 *      Author: lvanlv
 */

#ifndef EVENTLOOPTHREAD_H_
#define EVENTLOOPTHREAD_H_

#include <ThreadSyn.h>
#include <Thread.h>

namespace netlib{
namespace net{

class EventLoop;

class EventLoopThread{
public:
	typedef boost::function<void(EventLoop*)> ThreadInitCallback;

public:
	explicit EventLoopThread(ThreadInitCallback cb = ThreadInitCallback());
	~EventLoopThread();

	EventLoop* startLoop();

private:
	void threadFunc();

private:
	EventLoop* loop_;
	bool exit_;
	netlib::base::Thread thread_;
	netlib::base::ThreadMutex mutex_;
	netlib::base::ThreadCond cond_;
	ThreadInitCallback callBack_;
};

}
}

#endif /* EVENTLOOPTHREAD_H_ */
