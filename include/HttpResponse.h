/*
 * HttpResponse.h
 *
 *  Created on: Jan 23, 2014
 *      Author: lvanlv
 */

#ifndef HTTPREPONSE_H_
#define HTTPREPONSE_H_

#include <Buffer.h>

namespace netlib{
namespace net{

class HttpResponse
{
public:
	enum HttpStatusCode
	{
		kUnkown,
		k200ok = 200,
	    k301MovedPermanently = 301,
	    k400BadRequest = 400,
	    k404NotFound = 404,
	    k500ServerError = 500
	};

public:
	explicit HttpResponse(bool close)
	: httpStatus_(kUnkown),
	  closeConnection_(close)
	{}

	void appendToBuffer(Buffer* output);

	void setStatusCode(const HttpStatusCode& status)
	{
		httpStatus_ = status;
	}

	HttpStatusCode getStatusCode() const
	{
		return httpStatus_;
	}

	void setCloseConnection(bool close)
	{
		closeConnection_ = close;
	}

	void addHeader(const string& key, const string& value)
	{
		headers_[key] = value;
	}

	void setContentType(const string& content)
	{
		addHeader("Content-Type", content);
	}

	void setBody(const string& body)
	{
		body_ = body;
	}

	void setStatusMessage(const string& message)
	{
		statusMessage_ = message;
	}

private:
	std::map<std::string, std::string> headers_;
	HttpStatusCode httpStatus_;
	bool closeConnection_;
	string statusMessage_;
	string body_;

};

}
}

#endif /* HTTPREPONSE_H_ */
