/*
 * HttpResponse.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: lvanlv
 */

#include <HttpResponse.h>

namespace netlib{
namespace net{

void HttpResponse::appendToBuffer(Buffer* output)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "HTTP/1.1 %d ", httpStatus_);
	output->append(buf, strlen(buf));
	output->append(statusMessage_);
	output->append("\r\n");

	if(closeConnection_)
	{
		output->append("Connection: close\r\n");
	}
	else
	{
		snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
		output->append(buf, strlen(buf));
		output->append("Connection: Keep-Alive\r\n");
	}

	for(std::map<std::string, std::string>::iterator it = headers_.begin();
			it != headers_.end();
			++it)
	{
		output->append(it->first);
		output->append(": ");
		output->append(it->second);
		output->append("\r\n");
	}

	output->append("\r\n");
	output->append(body_);
}

}
}
