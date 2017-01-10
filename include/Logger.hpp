//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_LOGGER_H
#define MERSULTRENURILOR_LOGGER_H
#define DEBUG 1


class Logger {
    Logger () {}
    static Logger *singleton ;
public:
    static Logger& GetInstance();
    void logd (std::string message) const;
    void loge(std::string message) const;
    Logger& operator << (std::string);
    Logger& operator << (int);
};


#endif //MERSULTRENURILOR_LOGGER_H
