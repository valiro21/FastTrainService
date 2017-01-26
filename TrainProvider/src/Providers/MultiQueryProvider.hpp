//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_MULTIQUERYPROVIDER_HPP
#define FASTTRAINSERVICE_MULTIQUERYPROVIDER_HPP

#include <json/json.hpp>
#include <string>
#include <DatabaseManager.hpp>
#include <vector>
#include <DatabaseUtils.hpp>
#include <Logger.hpp>
#include "Provider.hpp"

using json = nlohmann::json;

class MultiQueryProvider : public Provider {
protected:
    virtual json provide(json request) {
        return json ();
    }
    json request;
public:
    MultiQueryProvider (json request);
    std::string type;
    json execute ();
};


#endif //FASTTRAINSERVICE_MULTIQUERYPROVIDER_HPP
