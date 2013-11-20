/*
 * Timer.h
 *
 *  Created on: Oct 29, 2013
 *      Author: lvanlv
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Thread.h>
#include <CallBacks.h>
#include <TimeStamp.h>
#include <Atomic.h>

namespace netlib{
namespace base{

class Timer
{
public:
	Timer(const netlib::net::TimerCallback& task, TimeStamp when, double interval = 0)
	:	task_(task),
	 	expiration_(when),
	 	interval_(interval),
	 	repeat_(interval > 0.0),
	 	sequence_(numCreated_.incrementAndGet())  //TODO  产生唯一的TimerID
	{}

	void run() const
	{
		task_();
	}

	TimeStamp expiration() const { return expiration_; }
	int64_t sequence() const { return sequence_;}
	bool repeat() const { return repeat_;}
	void restart(TimeStamp when);

	static int64_t numCreated() { return numCreated_.get(); }

private:
	netlib::net::TimerCallback task_;

	TimeStamp expiration_;
	const double interval_;
	const int64_t sequence_;  //sequence 连续 顺序 次序
	const bool repeat_;

	static AtomicInt64 numCreated_;
};

}
}

#endif /* TIMER_H_ */
