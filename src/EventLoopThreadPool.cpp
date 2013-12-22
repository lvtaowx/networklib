/*
 * EventLoopThreadPool.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#include <boost/implicit_cast.hpp>

#include <EventLoopThreadPool.h>
#include <EventLoop.h>
#include <EventLoopThread.h>

namespace netlib{
namespace net{

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop)
	: baseLoop_(baseLoop),
	  started_(false),
	  threadNums_(0),
	  next_(0)
{

}

EventLoopThreadPool::~EventLoopThreadPool()
{
	// Don't delete loop, it's stack variable
}

void EventLoopThreadPool::start(const ThreadInitCallBack& cb)
{
	assert(!started_);
	baseLoop_->assertInLoopThread();

	started_ = true;
	for(int i = 0; i < threadNums_; ++i)
	{
		EventLoopThread* t = new EventLoopThread(cb);
		threads_.push_back(t);
		loops_.push_back(t->startLoop());
	}
	if(threadNums_ == 0 && cb)
	{
		cb(baseLoop_);
	}
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
	baseLoop_->assertInLoopThread();
	EventLoop* loop = baseLoop_;
	if(!loops_.empty())
	{
//		loop = loops_.at(next_);
		loop = loops_[next_];
		++next_;
	    if (boost::implicit_cast<size_t>(next_) >= loops_.size())
	    {
	      next_ = 0;
	    }
	}

	return loop;
}

}
}


