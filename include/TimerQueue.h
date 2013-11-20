/*
 * TimerQueue.h
 *
 *  Created on: Oct 30, 2013
 *      Author: lvanlv
 */

#ifndef TIMERQUEUE_H_
#define TIMERQUEUE_H_

#include <boost/bind.hpp>

#include <CommonHeadFile.h>
#include <CallBacks.h>
#include <Channel.h>
#include <TimeStamp.h>
//#include <EventLoop.h>

namespace netlib{
namespace base{

using namespace netlib::net;

class netlib::net::EventLoop;
class Timer;
class TimerId;

class TimerQueue
{
public:
	TimerQueue(EventLoop* loop);
	~TimerQueue();

	TimerId addTimer(const TimerCallback& cb, TimeStamp when, double interval);
	void cancel(TimerId timerId);

private:
	typedef std::pair<TimeStamp, Timer*> Entry;
	typedef std::set<Entry> TimerList;
	typedef std::pair<Timer*, int64_t> ActiveTimer;
	typedef std::set<ActiveTimer> ActiveTimerSet;

private:
	void addTimerInLoop(Timer* timer);
	void cancelInLoop(TimerId timerId);
	bool insert(Timer* timer);
	void reset(const std::vector<Entry>& expired, TimeStamp now);
	std::vector<Entry> getExpired(TimeStamp when);
	void handleRead();

private:
	EventLoop* loop_;
	Channel timerChannel_;
	TimerList timers_;
	ActiveTimerSet activeTimers_; //用于一个未到期的
	ActiveTimerSet cancelTimers_;

	const int timerFd_;

	bool callingExpiredTimers_;
};

}
}

#endif /* TIMERQUEUE_H_ */
