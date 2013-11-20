/*
 * TimerQueue.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: lvanlv
 */

#define __STDC_LIMIT_MACROS //UINTPTR_MAX 为了展开 UINTPTR_MAX 在头文件 stdint.h中

#include <stdint.h>
#include <sys/timerfd.h>

#include <EventLoop.h>
#include <Timer.h>
#include <TimerId.h>
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

struct timespec howMuchTimeFromNow(TimeStamp when)
{
	int64_t microSeconds = when.microSecondsSinceEpoch() - TimeStamp::now().microSecondsSinceEpoch();

	if(microSeconds < 100)
	{
		microSeconds = 100;
	}

	struct timespec ts;
	ts.tv_sec = static_cast<time_t>( microSeconds / kMicroSecondsPerSecond );
	ts.tv_nsec = static_cast<long>( microSeconds % kMicroSecondsPerSecond * 1000);

	return ts;
}

void resetTimerFd(int timerfd, TimeStamp expiration)
{
	struct itimerspec newValue;
	struct itimerspec oldValue;
	bzero(&newValue, sizeof newValue);
	bzero(&oldValue, sizeof oldValue);

	newValue.it_value = howMuchTimeFromNow(expiration);
	int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
	if(ret)
	{
		printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	}
}

void readTimerFd(int timerFd, TimeStamp when)
{
	uint64_t howmany;
	ssize_t n = ::read(timerFd, &howmany, sizeof(howmany));
	printf("%s  %s  read size %zu \n", __FILE__, __FUNCTION__, n);
}

TimerQueue::TimerQueue(netlib::net::EventLoop* loop)
	: loop_(loop),
	  timerFd_(createTimerFd()),
	  timerChannel_(loop, timerFd_)
{
	timerChannel_.setReadCallBack(boost::bind(&TimerQueue::handleRead, this));
	timerChannel_.enableReading();
}

TimerQueue::~TimerQueue()
{
	::close(timerFd_);

	for(TimerList::iterator it = timers_.begin(); it != timers_.end(); ++it)
	{
		delete it->second;
	}
}

TimerId TimerQueue::addTimer(const TimerCallback& cb, TimeStamp when, double interval)
{
	Timer* timer = new Timer(cb, when, interval);
	loop_->runInLoop(boost::bind(&TimerQueue::addTimerInLoop, this, timer));

	return TimerId(timer, timer->sequence());
}

void TimerQueue::cancel(TimerId timerId)
{
	loop_->runInLoop(boost::bind(&TimerQueue::cancelInLoop, this, timerId));
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
	loop_->assertInLoopThread();
	bool earliestChanged = insert(timer);

	// 如果 新加入的定时器比第一个要到触发时间的定时器的 时间还要短，则要重置timerFd
	if(earliestChanged)
	{
		resetTimerFd(timerFd_, timer->expiration());
	}
}

void TimerQueue::cancelInLoop(TimerId timerId)
{
	loop_->assertInLoopThread();
	ActiveTimer timer(timerId.timer_, timerId.sequence_);
	ActiveTimerSet::iterator it = activeTimers_.find(timer);
	if(it != activeTimers_.end())
	{
		size_t n = timers_.erase(Entry(it->first->expiration(), it->first));
		assert(n == 1); (void)n;//TODO (void)n 陈硕老师说防止编译器警告，具体研究
		delete it->first;
		activeTimers_.erase(it);
	}
	else if(callingExpiredTimers_)
	{
		cancelTimers_.insert(timer);
	}
}

bool TimerQueue::insert(Timer* timer)
{
	loop_->assertInLoopThread();

	bool earliestChanged = false;
	TimeStamp when = timer->expiration();
	TimerList::iterator it = timers_.begin();
	if(it == timers_.end() || when < it->first)
	{
		// 如果 新加入的定时器比第一个要到触发时间的定时器的 时间还要短，则要重置timerFd
		earliestChanged = true;
	}

	{
		std::pair<TimerList::iterator, bool> result = \
		timers_.insert(Entry(when, timer));
		assert(result.second); (void)result;
	}

	{
		std::pair<ActiveTimerSet::iterator, bool> result = \
		activeTimers_.insert(ActiveTimer(timer, timer->sequence()));
		assert(result.second); (void)result;
	}

	return earliestChanged;
}

void TimerQueue::reset(const std::vector<Entry>& expired, TimeStamp now)
{
	TimeStamp nextExpired;
	for(std::vector<Entry>::const_iterator it = expired.begin(); it != expired.end(); ++it)
	{
		ActiveTimer aTimer(it->second, it->second->sequence());
		if(it->second->repeat() && cancelTimers_.find(aTimer) == cancelTimers_.end())
		{
			it->second->restart(now);
			insert(it->second);
		}
		else
		{
			delete it->second; //FIXME muduo 这里要求修复
		}
	}

	if(!timers_.empty())
	{
		nextExpired = timers_.begin()->second->expiration();
	}
	if(nextExpired.valid())
	{
		resetTimerFd(timerFd_, nextExpired);
	}
}

std::vector<TimerQueue::Entry> TimerQueue::getExpired(TimeStamp when)
{
	std::vector<TimerQueue::Entry> expired;

	/*
	 * 这里看了很久，关键是要明白 std::pair  重载操作符 operator > < ==等等
	 * 这是中重要的是 now 因为 pair 中的排序是看第一个来排序的，只有第一个不成功的情况下才看第二个的。
	 */
	Entry sentry(when, reinterpret_cast<Timer*>(UINTPTR_MAX));
	TimerList::iterator end = timers_.lower_bound(sentry);  //lower_bound  不小于
	assert(end == timers_.end() || when < end->first);

	/*
	 * Copies the elements in the range, defined by [first, last)  first是闭区间，last 是开区间。
	 * */
	std::copy(timers_.begin(), end, back_inserter(expired)); // 取出时间点在now 前面的定时器
	timers_.erase(timers_.begin(), end);

	//TODO activeTimers   删除到期的定时器
	for(std::vector<Entry>::iterator it = expired.begin(); it != expired.end(); ++it)
	{
		ActiveTimer timer(it->second, it->second->sequence());
		size_t n = activeTimers_.erase(timer);
		assert(n == 1);
	}

	return expired;  //expired 过期的 失效的
}

void TimerQueue::handleRead()
{
	loop_->assertInLoopThread();
	TimeStamp now(TimeStamp::now());
	readTimerFd(timerFd_, now);

	std::vector<Entry> expired = getExpired(now);

	callingExpiredTimers_ = true;//TODO 这里有疑问，若在多线程中会不会有,毕竟这里是无锁的
	cancelTimers_.clear();
	for(std::vector<Entry>::iterator it = expired.begin(); it < expired.end(); ++it)
	{
		it->second->run();
	}
	callingExpiredTimers_ = false;

	reset(expired, now);
}




}
}

