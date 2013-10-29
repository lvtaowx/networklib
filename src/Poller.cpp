/*
 * Poller.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: lvanlv
 */

#include <Poller.h>

namespace netlib{
namespace net{

Poller::Poller(EventLoop* loop)
	: ownerLoop_(loop)
{

}

Poller::~Poller()
{

}


}
}

