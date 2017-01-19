//
// Created by vrosca on 1/19/17.
//

#ifndef FASTTRAINSERVICE_DATABASEUTILS_HPP
#define FASTTRAINSERVICE_DATABASEUTILS_HPP


#include <neo4j-client.h>
#include <string>
#include <json/json.hpp>

using json = nlohmann::json;

class DatabaseUtils {
    static DatabaseUtils* singleton;
public:
    static DatabaseUtils& GetInstance ();


    std::string neo4j_raw_string (neo4j_value_t value);
    json neo4j_to_json (neo4j_value_t value);
};


#endif //FASTTRAINSERVICE_DATABASEUTILS_HPP
