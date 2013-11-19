/*
 * TimeStamp.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: lvanlv
 */

#include <sys/time.h>

#include <TimeStamp.h>

namespace netlib{
namespace base{

TimeStamp TimeStamp::now()
{
	/*
	 * 	struct timeval
		{
			__time_t tv_sec;       	Epoch到现在的秒数	 Seconds
			__suseconds_t tv_usec;  Epoch到现在的微妙数  Microseconds
		};
	 */
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seconds = tv.tv_sec;

	return TimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

TimeStamp TimeStamp::invalid()
{
	return TimeStamp();
}

}
}


