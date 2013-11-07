/*
 * TimerId.h
 *
 *  Created on: Nov 7, 2013
 *      Author: lvanlv
 */

#ifndef TIMERID_H_
#define TIMERID_H_

namespace netlib{
namespace base{

class Timer;

class TimerId
{
public:
	TimerId()
	: timer_(NULL),
	  sequence_(0)
	{
	}

	TimerId(Timer* timer, int64_t seq)
	: timer_(timer),
	  sequence_(seq)
	{
	}

	friend class TimerQueue;

private:
	Timer* timer_;
	int64_t sequence_;
};

}
}


#endif /* TIMERID_H_ */
