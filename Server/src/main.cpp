#include <JThread.hpp>
#include "../include/Server.hpp"

using namespace std;

int main() {
    Server *server = new Server(8181);

    server->start();
    server->join();

    return 0;
}