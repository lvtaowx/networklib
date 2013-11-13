/*
 * Timer.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: lvanlv
 */

#include <Timer.h>

namespace netlib{
namespace base{

void Timer::restart(TimeStamp when)
{
	if(repeat_)
	{
		expiration_ = addTime(when, interval_);
	}
	else
	{
		expiration_ = TimeStamp::invalid();
	}
}

}
}
