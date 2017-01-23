//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_CLIENTTHREAD_H
#define MERSULTRENURILOR_CLIENTTHREAD_H


#include <thread>
#include <atomic>
#include <mutex>
#include <JThread.hpp>
#include <bits/ios_base.h>
#include <iostream>
#include <Utils.hpp>
#include <Logger.hpp>
#include <RequestsPool.hpp>
#include <ProviderFactory.hpp>

class ClientThread : public JThread {
    int *client_fd;
    std::mutex *write_mutex;

public:
    ClientThread (int client_fd) {
        this->client_fd = new int(client_fd);
        write_mutex = new std::mutex();
    }

    ClientThread (const ClientThread &client) {
        this->client_fd = client.client_fd;
        write_mutex = new std::mutex();
    }

    void run ();
    void sendResponse (std::string response);

    ~ClientThread() {
        if (client_fd != nullptr) {
            delete client_fd;
            delete write_mutex;
        }
    }
};

#endif //MERSULTRENURILOR_CLIENTTHREAD_H
