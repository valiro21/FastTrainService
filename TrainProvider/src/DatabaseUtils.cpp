//
// Created by vrosca on 1/19/17.
//

#include <Logger.hpp>
#include "Utils.hpp"
#include "DatabaseUtils.hpp"
DatabaseUtils* DatabaseUtils::singleton = NULL;

DatabaseUtils& DatabaseUtils::GetInstance () {
    if (singleton == nullptr) {
        singleton = new DatabaseUtils();
    }
    return *singleton;
}

std::string DatabaseUtils::neo4j_raw_string (neo4j_value_t value) {
    char *buf = new char[2048];
    size_t nr;
    if ((nr = neo4j_ntostring(value, buf, 2048)) > 2048) {
        delete[] buf;
        buf = new char[nr+2];
        neo4j_ntostring(value, buf, 2048);
    }

    std::string result = buf;
    delete[] buf;

    return result;
}

std::string DatabaseUtils::neo4j_get_string (neo4j_value_t value) {
    char *buf = new char[2048];
    size_t nr;
    if ((nr = neo4j_ntostring(value, buf, 2048)) > 2048) {
        delete[] buf;
        buf = new char[nr+2];
        neo4j_ntostring(value, buf, 2048);
    }

    std::string result;
    if (buf[0] == '"') {
        result = std::string (buf + 1);
    }
    else {
        result = buf;
    }
    delete[] buf;
    if (result.back() == '"') result.pop_back();

    return result;
}

json DatabaseUtils::neo4j_to_json (neo4j_value_t value) {
    if (neo4j_type(value) == NEO4J_NODE) {
        neo4j_value_t value1 = neo4j_node_labels(value),
                value2 = neo4j_node_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value2))));
        return result;
    }
    else if (neo4j_type(value)) {
        neo4j_value_t value1 = neo4j_relationship_type(value),
                value2 = neo4j_relationship_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value2))));

        return result;
    }
    else {
        return json();
    }
}