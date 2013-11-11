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

private:
	typedef std::pair<TimeStamp, Timer*> Entry;
	typedef std::set<Entry> TimerList;

private:
	std::vector<Entry> getExpired();
	void handleRead();
	void addTimerInLoop(Timer* timer);
	bool insert(Timer* timer);

private:
	EventLoop* loop_;
	Channel timerChannel_;
	TimerList timers_;

	const int timerFd_;

};

}
}

#endif /* TIMERQUEUE_H_ */
