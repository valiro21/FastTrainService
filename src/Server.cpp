//
// Created by vrosca on 12/22/16.
//

#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <algorithm>
#include "Server.hpp"
#include "Logger.hpp"
#include "DatabaseManager.h"


Server::Server (int port) throw(std::ios_base::failure) {
    struct sockaddr_in svr_addr;

    //create socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        throw std::ios_base::failure("Cannot open socket");
    }
    bzero((char *) &svr_addr, sizeof(svr_addr));

    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons((uint16_t)port);
    inet_pton (AF_INET, "127.0.0.1", &svr_addr.sin_addr.s_addr);

    //bind socket
    if (bind(listen_fd, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) < 0) {
        throw std::ios_base::failure("Cannot bind to port " + std::to_string(port));
    }
}

void Server::run () throw(std::ios_base::failure) {
    if (DatabaseManager::initDB() == EXIT_FAILURE)
        throw std::ios_base::failure("Cannot connect to database!");

    listen(listen_fd, 5);
    while (true)
    {
        int client_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
        Logger::GetInstance().logd("Client accepted. Reading from socket " + std::to_string(client_fd));

        if (client_fd < 0)
            throw std::ios_base::failure("Cannot accept client");

        ClientThread *client = new ClientThread(client_fd);
        clients.push_back (client);
        client->attach_lambda([this, client]{ this->remove (client);});
        client->start();
    }
}

void Server::remove (ClientThread *thread) {
    clients_lock.lock();
    auto it = std::find(clients.begin(), clients.end(), thread);
    if (it != clients.end()) {
        clients.erase(it);
    }
    clients_lock.unlock();
}