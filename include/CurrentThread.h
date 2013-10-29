/*
 * CurrentThread.h
 *
 *  Created on: Oct 10, 2013
 *      Author: lvanlv
 */

#ifndef CURRENTTHREAD_H_
#define CURRENTTHREAD_H_

namespace netlib{
namespace CurrentThread{

extern __thread int t_cachedTid;
extern __thread char t_tidString[32];
extern __thread const char* t_threadName;

	void cachedTid();
	inline int tid()
	{
		if(t_cachedTid == 0)
		{
			cachedTid();
		}

		return t_cachedTid;
	}

	inline const char* tidString()
	{
		return t_tidString;
	}

	inline const char* name()
	{
		return t_threadName;
	}

	bool isInMainThread();
}
}


#endif /* CURRENTTHREAD_H_ */
