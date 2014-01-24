/*
 * HttpRequest.h
 *
 *  Created on: Jan 23, 2014
 *      Author: lvanlv
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <CommonHeadFile.h>

namespace netlib{
namespace net{

class HttpRequest
{
public:
	enum Method
	{
		kInvalid, kGet, kPost, kHead, kPut, kDelete
	};

	enum Version
	{
		kUnkown, kHttp10, kHttp11
	};

public:
	HttpRequest()
	  : method_(kInvalid),
	    version_(kUnkown)
	{}

	void setVserion(Version v)
	{
		version_ = v;
	}

	Version getVersion() const
	{
		return version_;
	}

	bool setMethd()
	{
		assert(method_ == kInvalid);


		return true;
	}

	Method getMethod() const
	{
		return method_;
	}

	void setPath()
	{

	}

	const std::string& getPath() const
	{

	}

private:
	Method method_;
	Version version_;
	std::string path_;
	std::map<std::string, std::string> headers_;

};

}}

#endif /* HTTPREQUEST_H_ */
