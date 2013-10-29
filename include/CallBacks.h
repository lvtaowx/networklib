/*
 * CallBacks.h
 *
 *  Created on: Sep 25, 2013
 *      Author: lvanlv
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace netlib{
namespace net{

class Buffer;
class TcpConnection;
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef boost::function<void()> TimerCallback;
typedef boost::function<void (const TcpConnectionPtr&)> ConnectionCallback;
typedef boost::function<void (const TcpConnectionPtr&)> CloseCallback;
typedef boost::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
typedef boost::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

// the data has been read to (buf, len)
typedef boost::function<void (const TcpConnectionPtr&,
                              Buffer*)> MessageCallback;

void defaultConnectionCallback(const TcpConnectionPtr& conn);
void defaultMessageCallback(const TcpConnectionPtr& conn,
                            Buffer* buffer);

}
}


#endif /* CALLBACKS_H_ */
