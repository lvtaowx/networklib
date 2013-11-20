/*
 * TimeStamp.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: lvanlv
 */

#include <sys/time.h>
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS

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

std::string TimeStamp::toString() const
{
	  char buf[32] = {0};
	  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
	  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
	  snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
	  return buf;
}

}
}


