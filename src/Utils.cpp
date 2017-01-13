//
// Created by vrosca on 12/21/16.
//

#include <cstring>
#include <Logger.hpp>
#include "Utils.hpp"

Utils* Utils::singleton = NULL;

Utils& Utils::GetInstance () {
    if (singleton == nullptr) {
        singleton = new Utils();
    }
    return *singleton;
}

int Utils::ReadInt (int fd) throw(std::ios_base::failure) {
    int x = 0; ssize_t nr;
    if ((nr = read(fd, &x, 4)) == -1 || nr != 4) {
        throw std::ios_base::failure("Failed to read int!");
    }
    return x;
}

Utils::Utils() {
    max_request_size = 40000;
    buffer_size = 2000;
    buffer = new char[2000];
}

bool Utils::check_size(size_t size){
    if (size > max_request_size) {
        return false;
    }

    if (size + 1 > buffer_size) {
        buffer_size = size + 1;
    }
    delete[] buffer;
    buffer = new char[buffer_size];

    return true;
}

std::string Utils::Read (int fd) throw(std::ios_base::failure) {
    size_t nrc = (size_t)ReadInt (fd);
    ssize_t nr;

    if (!check_size (nrc) || (nr = read (fd, buffer, nrc)) == -1 || nr != nrc)
        throw std::ios_base::failure("Failed to read string!");
    buffer[nrc] = '\0';
    std::string s(buffer);
    return s;
}

json Utils::ReadJSON (int fd) throw(std::ios_base::failure) {
    try {
        return json::parse(Utils::Read(fd));
    }
    catch (std::invalid_argument &e) {
        Logger::GetInstance().logd ("Request parse error: " + std::string(e.what()));
        return json();
    }
}

void Utils::Write (int fd, std::string message) throw(std::ios_base::failure){
    unsigned long size = message.size ();
    if ( write(fd, (char *)&size, 4) != 4 ||
         dprintf(fd, "%s", message.c_str()) != size )
        throw std::ios_base::failure(std::string ("Failed to write string: ") + strerror(errno) + " " + std::to_string(fd));
}

void Utils::WriteJSON (int fd, json message) throw(std::ios_base::failure){
    std::string str_message = message.dump();
    Write(fd, str_message);
}

std::regex Utils::regexp("([a-zA-Z][a-zA-Z0-9_]*[ ]*)(:)", std::regex_constants::basic);
std::string Utils::repair_json_string (std::string str) {
    return std::regex_replace(str, regexp, "\"$1\":");
}

#ifdef NEO4J_CLIENT_H
std::string Utils::neo4j_raw_string (neo4j_value_t value) {
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

json Utils::neo4j_to_json (neo4j_value_t value) {
    if (neo4j_type(value) == NEO4J_NODE) {
        neo4j_value_t value1 = neo4j_node_labels(value),
                value2 = neo4j_node_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::repair_json_string(Utils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::repair_json_string(Utils::neo4j_raw_string(value2))));

        return result;
    }
    else if (neo4j_type(value)) {
        neo4j_value_t value1 = neo4j_relationship_type(value),
                value2 = neo4j_relationship_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::repair_json_string(Utils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::repair_json_string(Utils::neo4j_raw_string(value2))));

        return result;
    }
    else {
        return json();
    }
}
#endif

std::string Utils::getErrorJSONString(std::string error) {
    return "{\"error\": \"" + error + "\"}";
}