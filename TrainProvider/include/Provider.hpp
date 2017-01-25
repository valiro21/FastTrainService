//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_PROVIDER_HPP
#define FASTTRAINSERVICE_PROVIDER_HPP

#include <json/json.hpp>
#include <string>
#include <DatabaseManager.hpp>
#include <vector>
#include <DatabaseUtils.hpp>
#include <Logger.hpp>

using json = nlohmann::json;

class Provider {
protected:
    virtual json provide(neo4j_result_stream_t *result_stream) {
        return json ();
    }
    std::string query;
public:
    std::string type;
    json execute ();
};


#endif //FASTTRAINSERVICE_PROVIDER_HPP
