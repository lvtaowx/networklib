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
	Timer(const netlib::net::TimerCallback& task, double interval)
	:	task_(task),
	 	interval_(interval)
	{}

	void run() const
	{
		task_();
	}

	void restart();

private:
	netlib::net::TimerCallback task_;
	const double interval_;
};


}
}

#endif /* TIMER_H_ */
