//
// Created by vrosca on 1/11/17.
//

#ifndef FASTTRAINSERVICE_CLIENT_HPP
#define FASTTRAINSERVICE_CLIENT_HPP


#include <functional>
#include <vector>
#include <JThread.hpp>
#include <atomic>
#include <future>
#include <json/json.hpp>

using json = nlohmann::json;

class Client : public JThread{
private:
    Client(std::string host = "", int port = 0);
    static Client *instance;
    int sock_fd;
    std::atomic<double> latitude, longitude;
public:
    std::promise< json> searchPromise;
    void run ();
    void updateLocation ();
    double getLongitude ();
    double getLatitude ();
    static Client& GetInstance ();
    std::vector<std::string> autocompleteUpdate (std::string text);
    void search ();
};


#endif //FASTTRAINSERVICE_CLIENT_HPP
