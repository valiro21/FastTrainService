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
#ifdef DEBUG
    std::cout << "Debug: " << message << '\n';
#endif
}

void Logger::loge (std::string message) const {
    std::cerr << "Error: " << message << '\n';
}