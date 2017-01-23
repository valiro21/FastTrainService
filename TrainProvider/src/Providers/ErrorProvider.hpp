//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_ERRORPROVIDER_HPP
#define FASTTRAINSERVICE_ERRORPROVIDER_HPP

#include "Provider.hpp"

class ErrorProvider : public Provider {
    json response;
public:
    ErrorProvider (std::string message);
    json provide(neo4j_result_stream_t *result_stream);
};


#endif //FASTTRAINSERVICE_ERRORPROVIDER_HPP
