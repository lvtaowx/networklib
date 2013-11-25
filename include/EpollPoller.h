/*
 * EpollPoller.h
 *
 *  Created on: Jun 19, 2013
 *      Author: lvanlv
 */

#ifndef EPOLLPOLLER_H_
#define EPOLLPOLLER_H_

#include <CommonHeadFile.h>
#include <sys/epoll.h>

#include <Poller.h>
#include <Channel.h>

#define MAXEPOLLSIZE 10000

namespace netlib{
namespace net{

class EpollPoller : public Poller{
public:
	typedef std::vector<Channel*> ChannelList;

	EpollPoller(EventLoop* loop);
	virtual ~EpollPoller();

	virtual TimeStamp poll(int timeoutMs, ChannelList *activeChannels);
	virtual void updateChannel(Channel *channel);
	virtual void removeChannel(Channel *channel);

private:
	void updateOpt(int operation, Channel *channel);
	void fillActiveChannels(int eventsNums, ChannelList *activeChannels);

private:
	static const int kInitEpollEventsSize = 16;
	typedef std::vector<struct epoll_event> EventList;
	typedef std::map<int, Channel*> ChannelMap;

	int epollfd_;
	EventList events_;
	ChannelMap channels_;

};

}
}



#endif /* EPOLLPOLLER_H_ */
