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
	 	triggerPoint_(when),
	 	interval_(interval)
	{}

	void run() const
	{
		task_();
	}


	void restart();

private:
	netlib::net::TimerCallback task_;

	TimeStamp triggerPoint_;
	const double interval_;
};


}
}

#endif /* TIMER_H_ */
