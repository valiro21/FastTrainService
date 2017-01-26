//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_PROVIDER_HPP
#define FASTTRAINSERVICE_PROVIDER_HPP

#include <json/json.hpp>
#include <string>
#include <DatabaseManager.hpp>
#include <vector>
#include <DatabaseUtils.hpp>
#include <Logger.hpp>
#include <neo4j-client.h>

using json = nlohmann::json;

class Provider {
public:
    std::string type;
    virtual json execute () = 0;
};


#endif //FASTTRAINSERVICE_PROVIDER_HPP
