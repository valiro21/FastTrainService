//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_TESTCLIENT_HPP
#define FASTTRAINSERVICE_TESTCLIENT_HPP

#include <sys/socket.h>
#include <Logger.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <Utils.hpp>

class TestClient {
    int sockfd;
public:

    TestClient(int port) {
        Logger::GetInstance().logd(std::to_string(port));
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            Logger::GetInstance().loge("Failed to create socket");
        }

        struct sockaddr_in serv_address;
        serv_address.sin_family = AF_INET;
        serv_address.sin_port = htons(port);

        inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr.s_addr);

        if (connect(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0) {
            Logger::GetInstance().loge("Connection to server failed\n");
            throw std::ios_base::failure("Connection to server failed!");
        }
    }


    int send(json msg) {
        Utils::GetInstance().WriteJSON(sockfd, msg);
    }

    json receive () {
        return Utils::GetInstance().ReadJSON(sockfd);
    }
};

#endif //FASTTRAINSERVICE_TESTCLIENT_HPP
