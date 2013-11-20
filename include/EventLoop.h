/*
 * EventLoop.h
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

//#include <Channel.h>
#include <CommonHeadFile.h>
#include <CurrentThread.h>
#include <CallBacks.h>
#include <TimerQueue.h>
#include <TimerId.h>
#include <TimeStamp.h>

namespace netlib{
namespace net{

using namespace netlib::base;

//class netlib::base::TimerQueue;
class Poller;
class Channel;

class EventLoop : boost::noncopyable{
public:
	typedef boost::function<void ()> Functor;

public:
	EventLoop();
	~EventLoop();

	void loop();
	void runInLoop(const Functor& func);
	void queueInLoop(const Functor& func);

	void updateChannel(Channel *channel);
	void removeChannel(Channel *channel);

	void quit();

	void assertInLoopThread();
	bool isInLoopThread(){ return threadId_ == netlib::CurrentThread::tid(); }

	static EventLoop* getEventLoopOfCurrentThread();

	TimerId runAt(const TimeStamp time, const TimerCallback& cb);
	TimerId runAfter(double delay, const TimerCallback& cb);
	TimerId runEvery(double interval, const TimerCallback& cb);
	void cancel(TimerId timerId);

private:
	typedef std::vector<Channel *> ChannelList;

	bool looping_;
	bool quit_;
	const pid_t threadId_;
	bool eventHandling_;

	ChannelList activeChannels_;
	Channel *currentActiveChannel_;

	boost::scoped_ptr<Poller> pollerPtr_;
	boost::scoped_ptr<TimerQueue> timerQueuePtr_;
};

}
}


#endif /* EVENTLOOP_H_ */
