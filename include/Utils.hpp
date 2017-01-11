//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_UTILS_H
#define MERSULTRENURILOR_UTILS_H


#include <string>
#include <exception>
#include <bits/ios_base.h>
#include <regex>
#include <unistd.h>
#include <neo4j-client.h>
#include "json/json.hpp"

using json = nlohmann::json;

class Utils {
    size_t buffer_size;
    size_t max_request_size;
    char* buffer;
    bool check_size(size_t size);
    static Utils *singleton;
    Utils();
    static std::regex regexp;

public:
    static Utils& GetInstance ();

    std::string Read (int fd) throw(std::ios_base::failure);
    json ReadJson (int fd) throw(std::ios_base::failure);
    int ReadInt (int fd) throw(std::ios_base::failure);
    void Write (int fd, std::string message);
    void WriteJson (int fd, json message);

    std::string repair_json_string (std::string str);
    std::string neo4j_raw_string (neo4j_value_t value);
    json neo4j_to_json (neo4j_value_t value);
    std::string getErrorJSONString(std::string error);
};

#endif //MERSULTRENURILOR_UTILS_H
