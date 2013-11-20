/*
 * Atomic.h
 *
 *  Created on: Nov 20, 2013
 *      Author: lvanlv
 */

#ifndef ATOMIC_H_
#define ATOMIC_H_

#include <stdint.h>

#include <boost/noncopyable.hpp>

namespace netlib{
namespace base{

template<typename T>
class AtomicInterT : boost::noncopyable
{
public:
	AtomicInterT()
		: value_(0)
	{}

	T get()
	{
		return __sync_val_compare_and_swap(&value_, 0, 0);
	}

	T getAndAdd(T x)
	{
		return __sync_fetch_and_add(&value_, x);
	}

	T addAndGet(T x)
	{
		return getAndAdd(x)+x;
	}

	T incrementAndGet()
	{
		return addAndGet(1);
	}

	T decrementAndGet()
	{
		return addAndGet(-1);
	}

	void add(T x)
	{
		getAndAdd(x);
	}

	void increment()
	{
		incrementAndGet();
	}

	void decrement()
	{
		decrementAndGet();
	}

	T getAndSet(T newValue)
	{
		return __sync_lock_test_and_set(&value_, newValue);
	}

private:
	T value_;
};

typedef AtomicInterT<int32_t> AtomicInt32;
typedef AtomicInterT<int64_t> AtomicInt64;

}
}

#endif /* ATOMIC_H_ */
