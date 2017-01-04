//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_THREADWORKER_H
#define MERSULTRENURILOR_THREADWORKER_H


#include <vector>
#include "JThread.hpp"
#include "RequestTask.hpp"

class RequestWorker : public JThread {
    std::function<void(std::string)> callback;
    json request;
    RequestTask *task;
    RequestWorker() {};

public:
    RequestWorker (json request, std::function<void(std::string)> callback, RequestTask *task) {
        this->request = request;
        this->callback = callback;
        this->task = task;
    }

    void run ();
};


#endif //MERSULTRENURILOR_THREADWORKER_H
