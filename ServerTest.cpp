// ServerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/asio.hpp>
#include "TCPServer.h"
#include "Logger.h"
#include "JSONParser.h"
#include "JSONNode.h"
#include <map>
#include "TestDecodable.h"
#include "EventQueue.h"
#include "EnumConverter.h"
#include "StringUtility.h"

using boost::asio::ip::tcp;

/*
using namespace std::placeholders;

class A
{
public:
    A()
    {
        Subscribe();
    }

    void Unsubscribe()
    {
        EventQueue::UnsubscribeFromEvent(_subscription);
    }

    void Subscribe()
    {
        std::function<void(std::shared_ptr<TestGE>)> func = std::bind(&A::OnTestGe, this, _1);
        _subscription = EventQueue::SubscribeToEvent<TestGE>(func);
    }

    void OnTestGe(std::shared_ptr<TestGE> obj)
    {
        Logger::Log("Uspjeh!");
    }

private:
    EventSubscription::Ptr _subscription;  
}; 

*/

int main()
{
    
    boost::asio::io_context io_context;
    TCPServer server(io_context);

    server.Run();
    io_context.run();

    Logger::Log("Zavrsio sam! Gasim se...");


    // TestGE test;
    // test.Test();

    /*
    std::stringstream ss("{ \"name\" : \"ivek\", \"level\" : 26 }");
    JSONNode::Ptr result = JSONParser::GetInstance().Decode(ss);

    TestDecodable a;

    a.Decode(std::static_pointer_cast<JSONObjectNode>(result));

    std::cout << a.GetName() << ", " << a.GetLevel() << std::endl;
    std::cout << a.Encode() << std::endl;
    
    A AObject;

    EventQueue::CallEvent(std::make_shared<TestGE>());
    EventQueue::CallEvent(std::make_shared<Test2GE>());
    EventQueue::Update();
    */
}