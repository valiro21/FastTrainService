//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP
#define FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP


#include "Provider.hpp"

class ArrivalsProvider : public Provider {
public:
    json provide (neo4j_result_stream_t * result_stream);
    ArrivalsProvider (std::string station, std::string city, std::string country, long long time);
};


#endif //FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP
