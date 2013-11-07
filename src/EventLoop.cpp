/*
 * EventLoop.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: lvanlv
 */

#include <EventLoop.h>
#include <Poller.h>
#include <EpollPoller.h>
#include <Channel.h>

const int kPollTimeMs = 10000;

namespace {

__thread netlib::net::EventLoop* t_loopInThisThread = 0;

}

namespace netlib{
namespace net{

EventLoop::EventLoop()
	: 	looping_(false),
	  	quit_(false),
	  	threadId_(netlib::CurrentThread::tid()),
	  	eventHandling_(false),
		pollerPtr_(new EpollPoller(this))
{
	if(t_loopInThisThread)
	{
		std::cout << "Another EventLoop in this thread  " << t_loopInThisThread << threadId_;
	}
	else
	{
		t_loopInThisThread = this;
	}
}

EventLoop::~EventLoop(){

}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
	return t_loopInThisThread;
}

void EventLoop::loop(){

	while(!quit_)
	{
		pollerPtr_->poll(kPollTimeMs, &activeChannels_);

		eventHandling_ = true;
		for(ChannelList::iterator iter = activeChannels_.begin(); iter != activeChannels_.end(); ++iter)
		{
			currentActiveChannel_ = *iter;
			currentActiveChannel_->handleEvent();
		}
		currentActiveChannel_ = NULL;
		eventHandling_ = false;
	}
}

void EventLoop::runInLoop(const Functor& func)
{
	if(isInLoopThread())
	{
		func();
	}
	else
	{
		queueInLoop(func);
	}

}

void EventLoop::queueInLoop(const Functor& func)
{
	//TODO
	printf("runn in unexpected. file %s, function %s\n", __FILE__, __FUNCTION__);
}

void EventLoop::updateChannel(Channel *channel)
{
	pollerPtr_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel)
{
	assert( channel->ownerLoop() == this );

	pollerPtr_->removeChannel(channel);
}

void EventLoop::quit()
{

}

void EventLoop::assertInLoopThread()
{
	if(!isInLoopThread())
	{
		//Todo
		printf(" not in loop thread, file is %s , FUNCTION is %s\n", __FILE__, __FUNCTION__);
	}
}


}
}


