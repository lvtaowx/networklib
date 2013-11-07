/*
 * TimerQueue.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: lvanlv
 */

#include <sys/timerfd.h>

#include <TimerQueue.h>

namespace netlib{
namespace base{

int createTimerFd()
{
	int timerFd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

	if(timerFd < 0)
	{
		printf("create timerfd failed! file %s function %s  line %d\n", __FILE__, __FUNCTION__, __LINE__);
	}

	return timerFd;
}

void readTimerFd(int timerFd, int when)
{
	uint64_t howmany;
	ssize_t n = ::read(timerFd, &howmany, sizeof(howmany));
	printf("%s  %s \n", __FILE__, __FUNCTION__);

}

TimerQueue::TimerQueue(netlib::net::EventLoop* loop)
	: loop_(loop),
	  timerFd_(createTimerFd()),
	  timerChannel_(loop, timerFd_)
{
	timerChannel_.setReadCallBack(boost::bind(&TimerQueue::handleRead, this));
	timerChannel_.enableReading();
}

void TimerQueue::addTimer(const TimerCallback& cb, TimeStamp when, double interval)
{
	Timer* timer = new Timer(cb, when, interval);

}

void TimerQueue::addTimerInLoop(Timer* timer)
{


}

void TimerQueue::insert(Timer* timer)
{

}

std::vector<TimerQueue::Entry> getExpired()
{
	std::vector<TimerQueue::Entry> expired;

}

void TimerQueue::handleRead()
{
	loop_->assertInLoopThread();
	TimeStamp now(TimeStamp::now());

}


}
}

