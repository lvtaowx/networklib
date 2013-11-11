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

namespace netlib{
namespace base{

class Timer
{
public:
	Timer(const netlib::net::TimerCallback& task, TimeStamp when, double interval)
	:	task_(task),
	 	expiration_(when),
	 	interval_(interval)
	{}

	void run() const
	{
		task_();
	}

	TimeStamp expiration() const { return expiration_; }
	int64_t sequence() const { return sequence_;}

private:
	netlib::net::TimerCallback task_;

	TimeStamp expiration_;
	const double interval_;
	const int64_t sequence_;
};


}
}

#endif /* TIMER_H_ */
