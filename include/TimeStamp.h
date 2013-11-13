/*
 * TimeStamp.h
 *
 *  Created on: Nov 5, 2013
 *      Author: lvanlv
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdint.h>

#include <CommonHeadFile.h>

namespace netlib{
namespace base{

#define kMicroSecondsPerSecond 1000000

class TimeStamp{
public:
	TimeStamp()
	: microSecondsSinceEpoch_(0)
	{
	}

	explicit TimeStamp(int64_t microSeconds)
		: microSecondsSinceEpoch_(microSeconds)
	{
	}

	int64_t microSecondsSinceEpoch() const
	{
		return microSecondsSinceEpoch_;
	}

//	bool operator<(const TimeStamp& rhs)
//	{
//		return this->microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
//	}
//
//	bool operator==(const TimeStamp& rhs)
//	{
//		return this->microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
//	}

	static TimeStamp now();
	static TimeStamp invalid();

private:
	int64_t microSecondsSinceEpoch_;

};

inline bool operator<(TimeStamp lhs, TimeStamp rhs)
{
	return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator>(TimeStamp lhs, TimeStamp rhs)
{
	return lhs.microSecondsSinceEpoch() > rhs.microSecondsSinceEpoch();
}

inline bool operator==(TimeStamp lhs, TimeStamp rhs)
{
	return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline TimeStamp addTime(TimeStamp timeStamp, double seconds)
{
	int64_t microSecond = static_cast<int64_t>(seconds * kMicroSecondsPerSecond);
	return TimeStamp(timeStamp.microSecondsSinceEpoch() + microSecond);
}

}
}



#endif /* TIMESTAMP_H_ */
