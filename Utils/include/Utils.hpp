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
#include <mutex>
#include "json/json.hpp"

using json = nlohmann::json;

/** Utilities for networking and conversions
 * Implements networking functions like Read and Write for
 * different type and conversions. Read and Writes are atomic
 * per file descriptor.
 */
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
    json ReadJSON (int fd) throw(std::ios_base::failure);
    int ReadInt (int fd) throw(std::ios_base::failure);
    void Write (int fd, std::string message) throw(std::ios_base::failure);
    void WriteJSON (int fd, json message) throw(std::ios_base::failure);
    std::map<char, std::string> ch;
    std::string repair_json_string (std::string str);
    std::string getErrorJSONString(std::string error);
    std::string diacritics_fix(std::string word);
    std::map<int, std::mutex> write_m;
    std::map<int, std::mutex> read_m;
};

#endif //MERSULTRENURILOR_UTILS_H
