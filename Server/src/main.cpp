#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <JThread.hpp>
#include "Server.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

using namespace std;

class Test : public JThread {
    void run () {
        cout << "Hello World!\n";
    }
};

int main() {
    Server *server = new Server(8181);

    server->start();

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        Logger::GetInstance().loge("Failed to create socket");
    }

    struct sockaddr_in serv_address;
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(8181);

    inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr.s_addr);

    sleep (2);

    if (connect(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0) {
        Logger::GetInstance().loge("Connection to server failed\n");
        return 1;
    }

    try {
        Utils::GetInstance().Write(sockfd, "{\"action\":\"arrivals\","
                "\"city\":\"Iasi\","
                "\"station\":\"Gara Nord\"}");
    }
    catch (std::ios_base::failure &f) {
        Logger::GetInstance().loge(f.what());
    }
    server->join();

    return 0;
}