/*
 * Thread.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#include <assert.h>

#include <stdio.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
//#include <sys/unistd.h>

#include <Thread.h>
#include <CurrentThread.h>

namespace netlib{

namespace CurrentThread{

__thread int t_cachedTid;
__thread char t_tidString[32];
__thread const char* t_threadName = "unknown";


}

namespace detail{

pid_t gettid()
{
	return static_cast<pid_t>(::syscall(SYS_gettid));
}

}

void CurrentThread::cachedTid()
{
	if(t_cachedTid == 0)
	{
		t_cachedTid = detail::gettid();

	}
}

bool CurrentThread::isInMainThread()
{
	return tid() == ::getpid();
}

}


namespace netlib{
namespace base{

struct ThreadData{
	typedef Thread::ThreadFunc ThreadFunc;
	ThreadFunc func_;

	ThreadData(const ThreadFunc& func)
	: func_(func)
	{
	}

	void runInThread()
	{
		try
		{
			func_();
		}
		catch(...)
		{
			printf("file %s, function %s\n", __FILE__, __FUNCTION__);
		}
	}

};

void* startThreadFunc(void *obj)
{
	ThreadData *data = static_cast<ThreadData*>(obj);
	data->runInThread();
	delete data;
	data = NULL;

	return NULL;
}


Thread::Thread(const ThreadFunc& func, const std::string& name)
	: started_(false),
	  joined_(false),
	  func_(func),
	  name_(name)
{

}

Thread::~Thread()
{
	if(started_ && !joined_)
	{
		pthread_detach(threadId_);
	}
}

void Thread::start()
{
	assert(!started_);
	started_ = true;

	ThreadData* data = new ThreadData(func_);
	/*
	 *  第一个参数为指向线程标识符的指针。
　　	 *  第二个参数用来设置线程属性。
　　	 *  第三个参数是线程运行函数的起始地址。
　　	 *  最后一个参数是运行函数的参数。
	 */
	if(pthread_create(&threadId_, NULL, &startThreadFunc, data))
	{
		started_ = false;
		delete data;
		printf("create thread failed\n");
	}
}

int Thread::join()
{
	assert(started_);
	assert(!joined_);

	joined_ = true;
	int ret = pthread_join(threadId_, NULL);
	return ret;
}

}
}
