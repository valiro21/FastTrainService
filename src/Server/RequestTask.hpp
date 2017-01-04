//
// Created by vrosca on 12/22/16.
//

#ifndef MERSULTRENURILOR_REQUESTTASK_H
#define MERSULTRENURILOR_REQUESTTASK_H


#include <string>
#include "../include/json/json.hpp"

using json = nlohmann::json;

class RequestTask {
public:
    RequestTask() {};
    virtual std::string solve (json request) = 0;
};


#endif //MERSULTRENURILOR_REQUESTTASK_H
