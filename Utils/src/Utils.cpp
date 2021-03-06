//
// Created by vrosca on 12/21/16.
//

#include <cstring>
#include <Logger.hpp>
#include <netinet/in.h>
#include "Utils.hpp"

Utils* Utils::singleton = NULL;

Utils& Utils::GetInstance () {
    if (singleton == nullptr) {
        singleton = new Utils();
    }
    return *singleton;
}

int Utils::ReadInt (int fd) throw(std::ios_base::failure) {
    unsigned int x = 0; ssize_t nr;
    if ((nr = read(fd, &x, 4)) == -1 || nr != 4) {
        throw std::ios_base::failure("Failed to read int!");
    }
    x = ntohl(x);
    return x;
}

Utils::Utils() {
    max_request_size = 400000;
    buffer_size = 2000;
    buffer = new char[2000];

    // Romanian diacritics
    ch['s'] = "ş";
    ch['t'] = "ţ";
    ch['a'] = "â|ă";
    ch['i'] = "î";
    ch['S'] = "Ş";
    ch['T'] = "Ţ";
    ch['A'] = "Â|Ă";
    ch['I'] = "Î";
}

bool Utils::check_size(size_t size){
    if (size > max_request_size) {
        return false;
    }

    if (size + 1 > buffer_size) {
        buffer_size = size + 1;

        delete[] buffer;
        buffer = new char[buffer_size];
    }

    return true;
}

std::string Utils::Read (int fd) throw(std::ios_base::failure) {
    std::mutex& mutex = read_m[fd];
    Logger::GetInstance().logd("Reading!");
    mutex.lock();
    Logger::GetInstance().logd("Got lock!");

    size_t nrc = (size_t)ReadInt (fd);
    int nr = 0;

    ssize_t nrt = 0;
    std::string result;
    while (check_size (nrc - nrt) && nrt < nrc && nr != -1) {
        nr = (int)read (fd, buffer, nrc - nrt);
        if (nr != 1) {
            buffer[nr] = '\0';
            result += std::string (buffer);
        }
        nrt += nr;
    }

    if (!check_size(nrc) || nr == -1 || result.size () != nrc) {
        mutex.unlock();
        throw std::ios_base::failure(std::string("Failed to read string: ")
                                     + std::to_string(nrc) + " "
                                     + std::to_string(max_request_size) + " "
                                     + std::to_string(nrt) + " "
                                     + strerror(errno) + " "
                                     + std::to_string(fd));
    }
    mutex.unlock();
    Logger::GetInstance().logd("Readed!");
    return result;
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
    std::mutex& mutex = write_m[fd];
    mutex.lock();

    unsigned int size = (unsigned int) message.size (), sizec;
    Logger::GetInstance().logd("Wrote: " + std::to_string(size));
    sizec = ntohl(size);
    if (write(fd, (char *)&sizec, 4) != 4 ||
         dprintf(fd, "%s", message.c_str()) != size ) {
        mutex.unlock();
        throw std::ios_base::failure(
                std::string("Failed to write string: ") + strerror(errno) + " " + std::to_string(fd));
    }
    mutex.unlock();
}

void Utils::WriteJSON (int fd, json message) throw(std::ios_base::failure){
    std::string str_message = message.dump();
    Write(fd, str_message);
}

std::regex Utils::regexp("([a-zA-Z][a-zA-Z0-9_]*[ ]*)(:)", std::regex_constants::basic);
std::string Utils::repair_json_string (std::string str) {
    return std::regex_replace(str, regexp, "\"$1\":");
}

std::string Utils::getErrorJSONString(std::string error) {
    return "{\"error\": \"" + error + "\"}";
}

std::string Utils::diacritics_fix(std::string word) {
    std::string fix;
    for (unsigned int i = 0; i < word.size (); i++) {
        if (ch.find (word[i]) != ch.end ()) {
            fix += "(";
            fix += word[i];
            fix +="|";
            fix += ch[word[i]];
            fix += ")";
        }
        else {
            fix += word[i];
        }
    }
    return fix;
}