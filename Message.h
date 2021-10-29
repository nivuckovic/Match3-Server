#pragma once

#include <boost/asio.hpp>

using namespace boost::asio::ip;

class Message
{
public:
	std::string Identifier;
	float Timestamp;

protected:
	Message() {};

};

