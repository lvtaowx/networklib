/*
 * EventLoopThreadPool.h
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#ifndef EVENTLOOPTHREADPOOL_H_
#define EVENTLOOPTHREADPOOL_H_

#include <boost/function.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <CommonHeadFile.h>

namespace netlib{
namespace net{

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool{
public:
	typedef boost::function<void (EventLoop*)> ThreadInitCallBack;

public:
	explicit EventLoopThreadPool(EventLoop* baseLoop);
	~EventLoopThreadPool();

	void setThreadNum(int threadNums){ threadNums_ = threadNums; }
	void start(const ThreadInitCallBack& cb = ThreadInitCallBack());
	EventLoop* getNextLoop();

private:
	EventLoop* baseLoop_;
	bool started_;
	int threadNums_;
	int next_;
	boost::ptr_vector<EventLoopThread> threads_;
	std::vector<EventLoop*> loops_;
};

}
}

#endif /* EVENTLOOPTHREADPOOL_H_ */
