//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_SERVERTEST_HPP
#define FASTTRAINSERVICE_SERVERTEST_HPP

#include <gtest/gtest.h>
#include <Server.hpp>
#include "TestClient.hpp"
#include <cstdlib>

class ServerTest : public ::testing::Test {
protected:
    Server *server;

    virtual void SetUp () {
        srand(time(0));
        if (ServerTest::server_port == 0)
            ServerTest::server_port = 8181 + rand () % 20;
    }
public:
    static int server_port;
    static TestClient* client;
};


#endif //FASTTRAINSERVICE_SERVERTEST_HPP
