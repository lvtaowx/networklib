/*
 * EpollPoller.cpp
 *
 *  Created on: Jun 19, 2013
 *      Author: lvanlv
 */

#include <poll.h>

#include <boost/static_assert.hpp>

#include <CommonHeadFile.h>

#include <EpollPoller.h>

BOOST_STATIC_ASSERT(EPOLLIN == POLLIN);
BOOST_STATIC_ASSERT(EPOLLOUT == POLLOUT);

#define EPOLL_ADD EPOLL_CTL_ADD
#define EPOLL_DEL EPOLL_CTL_DEL
#define EPOLL_MOD EPOLL_CTL_MOD

namespace {
	static const int kNew = -1;
	static const int kAdded = 1;
	static const int kDeleted = 2;
}

namespace netlib{
namespace net{

EpollPoller::EpollPoller(EventLoop* loop)
	:	Poller(loop),
	    epollfd_(::epoll_create(MAXEPOLLSIZE)),
	    events_(kInitEpollEventsSize)
{

	if(epollfd_ < 0){
		printf("epoll create failed!   EpollPoller::EpollPoller() \n");
	}

}

EpollPoller::~EpollPoller()
{
	::close(epollfd_);
}

TimeStamp EpollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{

#ifdef DEBUG
int size = events_.size();
#endif

	int eventsNums = epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeoutMs);

	TimeStamp now(TimeStamp::now());
	if(eventsNums > 0){
		//TODO read   write
		fillActiveChannels(eventsNums, activeChannels);

		if(eventsNums == events_.size())
		{
			events_.resize(events_.size() * 2);
		}
	}
	else if(eventsNums == 0){
		//nothing
	}
	else{
		// error
	}

	return now;
}

void EpollPoller::updateChannel(Channel *channel)
{
	const int index = channel->index();
	if(index == kNew || index == kDeleted)
	{
		int fd = channel->fd();
		channels_[fd] = channel;

		channel->set_index(kAdded);
		updateOpt(EPOLL_ADD, channel);
	}
	else
	{
		//TODO
	}

}

void EpollPoller::removeChannel(Channel *channel)
{
	Poller::assertInLoopThread(); // father member method
	int fd = channel->fd();
	assert(channels_.find(fd) != channels_.end());
	assert(channels_[fd] == channel);
	assert(channel->isNoneEvent());

	int index = channel->index();
	assert(index == kAdded || index == kDeleted);

	size_t n = channels_.erase(fd);
	assert(n == 1);

	if(index == kAdded)
	{
		updateOpt(EPOLL_CTL_DEL, channel);
	}
	channel->set_index(kNew);
}

void EpollPoller::updateOpt(int operation, Channel *channel)
{
	struct epoll_event event;
	bzero(&event, sizeof(event));
	event.events = channel->events();
	event.data.ptr = channel;
	int fd = channel->fd();;

	int error  = ::epoll_ctl(epollfd_, operation, fd, &event);
	if (error < 0) {
	    printf("bind failed!  the error info %d  %s\n", errno, strerror(errno));
	    perror(strerror(errno));
	    return;
	}

}


void EpollPoller::fillActiveChannels(int eventsNums, ChannelList *activeChannels)
{

	for(int i = 0; i < eventsNums; ++i)
	{
		Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
		channel->set_revents(events_[i].events);

		//int fd = channel->fd();

		activeChannels->push_back(channel);
	}

}

}
}



