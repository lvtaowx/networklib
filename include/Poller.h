/*
 * Poller.h
 *
 *  Created on: Jun 19, 2013
 *      Author: lvanlv
 */

#ifndef POLLER_H_
#define POLLER_H_

#include <boost/noncopyable.hpp>

#include <CommonHeadFile.h>
#include <Channel.h>
#include <EventLoop.h>

namespace netlib{
namespace net{

class Poller : boost::noncopyable {
public:
	typedef std::vector<Channel*> ChannelList;

	Poller(EventLoop* loop);
	virtual ~Poller();

	virtual void poll(int timeoutMs, ChannelList *activeChannels) = 0;
	virtual void updateChannel(Channel *channel) = 0;
	virtual void removeChannel(Channel *channel) = 0;

//	static Poller* newDefualtPoller(EventLoop* loop) {};

	void assertInLoopThread()
	{
		ownerLoop_->assertInLoopThread();
	}

private:
	EventLoop* ownerLoop_;
};

}
}



#endif /* POLLER_H_ */
