/*
 * ThreadPool.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#include <stdio.h>

#include <boost/bind.hpp>

#include <ThreadPool.h>

namespace netlib{
namespace base{

ThreadPool::ThreadPool(const std::string& name)
	: running_(false),
	  maxQueueSize_(0),
	  mutex_(),
	  notEmpty_(mutex_),
	  notFull_(mutex_),
	  name_(name)
{

}

ThreadPool::~ThreadPool()
{
	if(running_)
	{
		stop();
	}
}

void ThreadPool::start(int numThreads)
{
	assert(threads_.empty());
	running_ = true;

	threads_.reserve(numThreads);
	for(int i = 0; i < numThreads; ++i)
	{
		threads_.push_back(new Thread(boost::bind(&ThreadPool::runInThread, this)));
		threads_[i].start();
	}

}

void ThreadPool::stop()
{
	{
		MutexLockGuard lock(mutex_);
		running_ = false;
		notEmpty_.notifyAll(); //important  why
	}
	for_each(threads_.begin(), threads_.end(), boost::bind(&Thread::join, _1));
}

void ThreadPool::run(const Task& task)
{
	if(threads_.empty())
	{
		task();
	}
	else
	{
		MutexLockGuard lock(mutex_);
		while(isFull())
		{
			notFull_.wait(); //为什么要用循环语句，不用if语句
		}

		queue_.push_back(task);
		notEmpty_.notify();
	}

}

bool ThreadPool::isFull() const
{
	return maxQueueSize_ > 0 && queue_.size() >= maxQueueSize_;
}

ThreadPool::Task ThreadPool::take()
{
	MutexLockGuard lock(mutex_);
	while(queue_.empty() && running_)
	{
		notEmpty_.wait();
	}

	Task task;
	if(!queue_.empty())
	{
		task = queue_.front();
		queue_.pop_front();
		if(maxQueueSize_ > 0)
		{
			notFull_.notify();         //如果deque是大于0的那么在删除其中的一个元素后自然是不满的
		}
	}

	return task;
}

void ThreadPool::runInThread()
{
	try
	{
		while(running_)
		{
			Task task(take());
			if(task)
			{
				task();
			}
		}
	}
	catch(...)
	{
		printf("%s  %s Exception\n", __FILE__, __FUNCTION__);
	}

}

}
}


