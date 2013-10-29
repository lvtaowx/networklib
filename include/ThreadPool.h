/*
 * ThreadPool.h
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <deque>

#include <boost/ptr_container/ptr_vector.hpp>
//#include <boost/ptr_container/ptr_container.hpp>

#include <Thread.h>
#include <ThreadSyn.h>

namespace netlib{
namespace base{

class ThreadPool{
public:
	typedef boost::function<void ()> Task;

	ThreadPool(const std::string& name = std::string());
	~ThreadPool();

	void setMaxQueueSize(int maxSize){ maxQueueSize_ = maxSize;}

	void start(int numThreads);
	void stop();
	void run(const Task& task); // add task

private:
	bool isFull() const;
	Task take();
	void runInThread();

private:
	ThreadMutex mutex_;
	ThreadCond notEmpty_;
	ThreadCond notFull_;

	std::string name_;
	size_t maxQueueSize_;
	boost::ptr_vector<Thread> threads_;
	std::deque<Task> queue_;

	bool running_;
};

}
}

#endif /* THREADPOOL_H_ */
