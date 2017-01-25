//
// Created by vrosca on 12/21/16.
//
#include "ClientThread.hpp"

void ClientThread::run () {
    try {
        while (true) {
            json request = json();
            request = Utils::GetInstance().ReadJSON(*client_fd);
            Logger::GetInstance().logd(request.dump());

            RequestsPool::GetInstance().execute ([request, this]() {
                Provider *provider = ProviderFactory::GetInstance().produce(request);
                json response = provider->execute();
                this->sendResponse(response);
            });
        }
    }
    catch (std::ios_base::failure failure) {
        // closed connection of broke fd
        Logger::GetInstance ().logd ("Client disconnected!");
        close (*client_fd);
    }
}

void ClientThread::sendResponse (json response) {
    write_mutex->lock ();
    Logger::GetInstance().logd("Response: " + response.dump());
    Utils::GetInstance().WriteJSON(*client_fd, response);
    write_mutex->unlock();
}