//
// Created by vrosca on 12/21/16.
//

#include <iostream>
#include "Logger.hpp"

Logger* Logger::singleton = NULL;

Logger& Logger::GetInstance () {
    if (singleton == nullptr) {
        singleton = new Logger();
    }
    return *singleton;
}

void Logger::logd (std::string message) const {
#ifndef RELEASE
    std::cout << "Debug: " << message << '\n';
#endif
}

void Logger::loge (std::string message) const {
    std::cerr << "Error: " << message << '\n';
}

Logger& Logger::operator <<(std::string str) {
    std::cout << str;
    return *this;
}

Logger& Logger::operator <<(int nr) {
    std::cout << nr;
    return *this;
}