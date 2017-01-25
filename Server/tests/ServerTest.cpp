//
// Created by vrosca on 1/25/17.
//

#include <Calendar.hpp>
#include "ServerTest.hpp"

int ServerTest::server_port = 0;
TestClient* ServerTest::client = nullptr;

TEST_F(ServerTest, ServerLoad) {
    try {
        server = new Server(ServerTest::server_port);
        server->start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    catch (std::exception *e) {
        FAIL() << "Expected server to succeed!";
    }
}

TEST_F(ServerTest, ConnectionTest) {
    try {
        ServerTest::client = new TestClient(ServerTest::server_port);
    }
    catch (std::exception *e) {
        FAIL() << "Expected Client to connect to Server";
    }
}

TEST_F(ServerTest, SendDeparturesRequest) {
    try {
        json request = json ();
        Calendar c;
        request["station"] = "Iaşi";
        request["country"] = "Romania";
        request["calendar"] = c.toJSON();
        ServerTest::client->send(request);
    }
    catch (std::exception *e) {
        FAIL() << "Expected successful write to server!";
    }
}

TEST_F(ServerTest, RecieveDeparturesRequest) {
    try {
        auto future = std::async(std::launch::async, [&](){return ServerTest::client->receive();});
        auto result = future.wait_for (std::chrono::seconds(10000));
        if (result == std::future_status::timeout) {
            FAIL() << "Request took too long";
        }
    }
    catch (std::exception *e){
        FAIL() << "Expected successful read from server!";
    }
}