//
// Created by vrosca on 12/22/16.
//

#ifndef MERSULTRENURILOR_REQUESTWORKERFACTORY_H
#define MERSULTRENURILOR_REQUESTWORKERFACTORY_H


#include "RequestWorker.hpp"

class SendBack : public RequestTask {
public:
    std::string solve (std::string request) {
        return request;
    }
};

class RequestTaskFactory {
    RequestTaskFactory () {}
    static RequestTaskFactory *singleton ;
public:
    static RequestTaskFactory& GetInstance();
    RequestTask* getTask (json request) throw (std::domain_error);
};


#endif //MERSULTRENURILOR_REQUESTWORKERFACTORY_H
