/*
 * Thread.h
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <string>
#include <pthread.h>

#include <boost/function.hpp>

namespace netlib{
namespace base{

class Thread{
public:
	typedef boost::function<void ()> ThreadFunc;

	explicit Thread(const ThreadFunc& func, const std::string& name = std::string());
	~Thread();

	void start();
	int join(); // return 0 is success, and the number is the error number

	bool started() const { return started_;}
	bool joined() const { return joined_;}

private:
	bool started_;
	bool joined_;

	std::string name_;
	pthread_t threadId_;
	ThreadFunc func_;
};

}
}

#endif /* THREAD_H_ */
