//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP
#define FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP


#include "SingleQueryProvider.hpp"
#include <Calendar.hpp>

class ArrivalsProvider : public SingleQueryProvider {
public:
    json provide (neo4j_result_stream_t * result_stream);
    ArrivalsProvider (std::string station, std::string country, Calendar time);
};


#endif //FASTTRAINSERVICE_ARRIVALSPROVIDER_HPP
