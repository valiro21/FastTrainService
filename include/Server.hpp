//
// Created by vrosca on 12/22/16.
//

#ifndef MERSULTRENURILOR_SERVER_H
#define MERSULTRENURILOR_SERVER_H


#include <bits/ios_base.h>
#include <vector>
#include <arpa/inet.h>
#include "../src/Server/ClientThread.hpp"

class Server : public JThread {
    int listen_fd;
    std::vector<ClientThread*> clients;
    std::mutex clients_lock;
public:
    Server (int port) throw(std::ios_base::failure);
    void remove (ClientThread *t);
    void run() throw (std::ios_base::failure);
};


#endif //MERSULTRENURILOR_SERVER_H
