#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class Socket
{
public:
	Socket(tcp::socket& tmpSocket) : _socket(tmpSocket) {};



private:
	tcp::socket& _socket;
};

