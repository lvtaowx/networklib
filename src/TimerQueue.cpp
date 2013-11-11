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

void resetTimerFd(int timerfd, TimeStamp expiration)
{
	struct itimerspec newValue;
	struct itimerspec oldValue;
	bzero(&newValue, sizeof newValue);
	bzero(&oldValue, sizeof oldValue);

	newValue.it_value = 0;//TODO
	int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
	if(ret)
	{
		printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	}
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

TimerId TimerQueue::addTimer(const TimerCallback& cb, TimeStamp when, double interval)
{
	Timer* timer = new Timer(cb, when, interval);
	loop_->runInLoop(boost::bind(&TimerQueue::addTimerInLoop, this, timer));

	return TimerId(timer, timer->sequence());
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
	loop_->assertInLoopThread();
	bool earliestChanged = insert(timer); //TODO

	if(earliestChanged)
	{
		resetTimerFd(timerFd_, timer->expiration());
	}
}

bool TimerQueue::insert(Timer* timer)
{
	loop_->assertInLoopThread();

	bool earliestChanged = false;
	TimeStamp when = timer->expiration();
	TimerList::iterator it = timers_.begin();
	if(it == timers_.end() || when < it->first) //TODO 没有看明白
	{
		earliestChanged = true;
	}

	{
		timers_.insert(Entry(when, timer));
	}

	{
		//TODO  activeTimers
	}

	return earliestChanged;
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

