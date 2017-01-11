//
// Created by vrosca on 1/11/17.
//

#include <netinet/in.h>
#include <bits/ios_base.h>
#include <memory.h>
#include <arpa/inet.h>
#include <Utils.hpp>
#include <QLocation>
#include <QtPositioning/QGeoLocation>
#include "Client.hpp"

Client* Client::instance = nullptr;

Client::Client(std::string host, int port) {
    latitude = 0;
    longitude = 0;
    if (port == 0)
        port = 8181;
    if (host == "") {
        host = "localhost";
    }

    struct sockaddr_in svr_addr;

    //create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        throw std::ios_base::failure("Cannot open socket");
    }
    bzero((char *) &svr_addr, sizeof(svr_addr));

    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons((uint16_t)port);
    inet_pton (AF_INET, host.c_str(), &svr_addr.sin_addr.s_addr);

    connect (sock_fd, (sockaddr*)&svr_addr, sizeof(svr_addr));
}

void Client::updateLocation () {
    //QGeoLocation *location = new QGeoLocation();
}

double Client::getLongitude () {
    return longitude;
}

double Client::getLatitude () {
    return latitude;
}

void Client::run () {
    while (true) {
        updateLocation ();
        sleep (10);
    }
}

Client& Client::GetInstance () {
    if (instance == nullptr) {
        instance = new Client();
    }
    return *instance;
}

std::vector<std::string> Client::autocompleteUpdate (std::string text) {

    json request;
    request["action"] = "autocomplete";
    request["prefix"] = "text";
    request["longitude"] = getLongitude ();
    request["latitude"] = getLatitude ();

    try {
        Utils::GetInstance().WriteJson(sock_fd, request);
        json response = Utils::GetInstance().ReadJson(sock_fd);
        std::vector<std::string> res = response.get<std::vector<std::string> >();
        return res;
    }
    catch (std::ios_base::failure &e) {
        //failed to read from
        std::vector<std::string> res;
        res.push_back (text + " - Could not retrive stations");
        return res;
    }

}