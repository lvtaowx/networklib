/*
 * EventLoopThread.cpp
 *
 *  Created on: Aug 30, 2013
 *      Author: lvanlv
 */

#include <boost/bind.hpp>

#include <EventLoopThread.h>
#include <EventLoop.h>

namespace netlib{
namespace net{

EventLoopThread::EventLoopThread(ThreadInitCallback cb)
	: loop_(NULL),
	  exit_(false),
	  thread_(boost::bind(&EventLoopThread::threadFunc, this)),
	  mutex_(),
	  cond_(mutex_),
	  callBack_(cb)
{

}


EventLoopThread::~EventLoopThread()
{
	exit_ = true;
	loop_->quit();
	thread_.join();
}

EventLoop* EventLoopThread::startLoop()
{
	assert(thread_.started());
	thread_.start();

	{
		netlib::base::MutexLockGuard lock(mutex_);
		while(loop_ == NULL)
		{
			cond_.wait();
		}
	}

	return loop_;
}

void EventLoopThread::threadFunc()
{
	EventLoop loop;

	if(callBack_)
	{
		callBack_(&loop);
	}

	{
		netlib::base::MutexLockGuard lock(mutex_);
		loop_ = &loop;
		cond_.notify();
	}

	loop.loop();
}

}
}


