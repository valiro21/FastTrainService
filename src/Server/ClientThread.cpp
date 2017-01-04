//
// Created by vrosca on 12/21/16.
//

#include <bits/ios_base.h>
#include <iostream>
#include "ClientThread.hpp"
#include "Utils.hpp"
#include "Logger.hpp"
#include "RequestsPool.hpp"

void ClientThread::run () {
    std::string request;
    try {
        while (true) {
            request = Utils::GetInstance().Read(*client_fd);
            Logger::GetInstance().logd(request + " request");
            RequestsPool::GetInstance().execute (request, [this](std::string response) {this->sendResponse(response);});
        }
    }
    catch (std::ios_base::failure failure) {
        // closed connection of broke fd
        Logger::GetInstance ().logd ("Client disconnected!");
        close (*client_fd);
    }
}

void ClientThread::sendResponse (std::string response) {
    write_mutex->lock ();
    Logger::GetInstance().logd("Response: " + response);
    Utils::GetInstance().Write(*client_fd, response);
    write_mutex->unlock();
}