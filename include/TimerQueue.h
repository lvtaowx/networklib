/*
 * TimerQueue.h
 *
 *  Created on: Oct 30, 2013
 *      Author: lvanlv
 */

#ifndef TIMERQUEUE_H_
#define TIMERQUEUE_H_

#include <CallBacks.h>
#include <Channel.h>
#include <EventLoop.h>
#include <Timer.h>
#include <TimeStamp.h>

namespace netlib{
namespace base{

using namespace netlib::net;

class TimerQueue
{
public:
	TimerQueue(EventLoop* loop);
	~TimerQueue();

	void addTimer(const TimerCallback& cb, TimeStamp when, double interval);

private:
	typedef std::pair<TimeStamp, Timer*> Entry;
	typedef std::set<Timer> TimerList;

private:
	std::vector<Entry> getExpired();
	void handleRead();
	void addTimerInLoop(Timer* timer);
	void insert(Timer* timer);

private:
	EventLoop* loop_;
	Channel timerChannel_;
	TimerList timers_;

	const int timerFd_;

};

}
}

#endif /* TIMERQUEUE_H_ */