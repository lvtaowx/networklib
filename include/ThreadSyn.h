/*
 * ThreadSyn.h
 *
 *  Created on: Mar 18, 2013
 *      Author: RichardLv
 */

#ifndef THREADSYN_H_
#define THREADSYN_H_

#include <assert.h>

#include <boost/utility.hpp>

#include <pthread.h>

namespace netlib{
namespace base{

class ThreadMutex : boost::noncopyable {
public:
	ThreadMutex(){
		int ret = pthread_mutex_init(&mutexLock_, NULL);
		assert( ret == 0);
		(void) ret; //XXX 有什么作用  抄自muduo
	}

	~ThreadMutex(){
		int ret = pthread_mutex_destroy(&mutexLock_);
		assert( ret == 0);
		(void) ret;
	}

	inline bool lock(){
		pthread_mutex_lock(&mutexLock_);
		return true;
	}
	bool unlock(){
		pthread_mutex_unlock(&mutexLock_);
		return true;
	}
	bool trylock(){
		pthread_mutex_trylock(&mutexLock_);
		return true;
	}

	pthread_mutex_t* getPThreadMutex()
	{
		return &mutexLock_;
	}

private:
	pthread_mutex_t mutexLock_;
};

class MutexLockGuard : boost::noncopyable{
public:
	explicit MutexLockGuard(ThreadMutex& mutex) : mutex_(mutex)
	{
		mutex_.lock();
	}

	~MutexLockGuard()
	{
		mutex_.unlock();
	}

private:
	ThreadMutex& mutex_; //这个类不能被拷贝  需要书写拷贝构造函数之后才行
};

class ThreadCond : boost::noncopyable{
public:
	ThreadCond(ThreadMutex& mutex) : condMutex_(mutex)
	{
		pthread_cond_init(&threadCond_, NULL);
//		pthread_mutex_init(&condMutex_, NULL);
	}

	~ThreadCond()
	{
		pthread_cond_destroy(&threadCond_);
//		pthread_mutex_destroy(&condMutex_);
	}

//	inline bool condLock()
//	{
//		pthread_mutex_lock(&condMutex_);
//		return true;
//	}
//
//	inline bool condUnlock()
//	{
//		pthread_mutex_unlock(&condMutex_);
//		return true;
//	}

	inline bool wait()
	{
		pthread_cond_wait(&threadCond_, condMutex_.getPThreadMutex());
		return true;
	}

	inline bool notify()
	{
		pthread_cond_signal(&threadCond_);
		return true;
	}

	inline bool notifyAll()
	{
		pthread_cond_broadcast(&threadCond_);
		return true;
	}

	bool waitForSeconds(int seconds)
	{
		//TODO

		return true;
	}

private:
	pthread_cond_t threadCond_;
	ThreadMutex& condMutex_; //这个类不能被拷贝  需要书写拷贝构造函数之后才行

	//TODO  设置线程属性、优先级等
};

}}


#endif /* THREADSYN_H_ */
