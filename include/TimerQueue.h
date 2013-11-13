/*
 * TimerQueue.h
 *
 *  Created on: Oct 30, 2013
 *      Author: lvanlv
 */

#ifndef TIMERQUEUE_H_
#define TIMERQUEUE_H_

#include <CommonHeadFile.h>

#include <boost/bind.hpp>

#include <CallBacks.h>
#include <Channel.h>
#include <EventLoop.h>
#include <Timer.h>
#include <TimerId.h>
#include <TimeStamp.h>

namespace netlib{
namespace base{

using namespace netlib::net;

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

	const int timerFd_;

	bool callingExpiredTimers_;
};

}
}

#endif /* TIMERQUEUE_H_ */
