/*
 * HttpContent.h
 *
 *  Created on: Jan 24, 2014
 *      Author: lvanlv
 */

#ifndef HTTPCONTENT_H_
#define HTTPCONTENT_H_

#include <HttpRequest.h>

namespace netlib{
namespace net{

class HttpContent
{
public:
	enum HttpRequestParseState
	{
		kExpectRequestLine,
		kExpectHeaders,
		kExpectBodys,
		kGotAll
	};

public:
	HttpContent()
	: state_(kExpectRequestLine)
	{}

	bool expectRequestLine() const
	{
		return state_ == kExpectRequestLine;
	}

	bool expectHeaders() const
	{
		return state_ == kExpectHeaders;
	}

	bool expectBodys() const
	{
		return state_ == kExpectBodys;
	}

	bool gotAll() const
	{
		return state_ == kGotAll;
	}

	void reset()
	{
		state_ = kExpectRequestLine;
		HttpRequest dummy;
		//TODO
	}

	const HttpRequest& request() const
	{
		return httpRequest_;
	}

	HttpRequest& request()
	{
		return httpRequest_;
	}

private:
	HttpRequestParseState state_;
	HttpRequest httpRequest_;
};

}
}


#endif /* HTTPCONTENT_H_ */
