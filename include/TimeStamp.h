/*
 * TimeStamp.h
 *
 *  Created on: Nov 5, 2013
 *      Author: lvanlv
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

namespace netlib{
namespace base{

#define kMicroSecondsPerSecond 1000000

class TimeStamp{
public:
	TimeStamp()
	: microSecondsSinceEpoch_(0)
	{
	}

	int64_t microSecondsSinceEpoch() const
	{
		return microSecondsSinceEpoch_;
	}

	bool operator<(const TimeStamp& rhs)
	{
		return this->microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
	}

	bool operator==(const TimeStamp& rhs)
	{
		return this->microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
	}

	static TimeStamp now();

private:
	int64_t microSecondsSinceEpoch_;

};

}
}



#endif /* TIMESTAMP_H_ */
