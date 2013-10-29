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

namespace netlib{
namespace net{

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

private:
	typedef std::vector<Channel *> ChannelList;

	bool looping_;
	bool quit_;
	const pid_t threadId_;
	bool eventHandling_;

	ChannelList activeChannels_;
	Channel *currentActiveChannel_;

	boost::scoped_ptr<Poller> pollerPtr_;


};

}
}


#endif /* EVENTLOOP_H_ */
