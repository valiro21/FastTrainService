//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_ERRORPROVIDER_HPP
#define FASTTRAINSERVICE_ERRORPROVIDER_HPP

#include "SingleQueryProvider.hpp"
/** Returns an error message as a json
 */
class ErrorProvider : public SingleQueryProvider {
    json response;
public:
    ErrorProvider (std::string message);
    json provide(neo4j_result_stream_t *result_stream);
};


#endif //FASTTRAINSERVICE_ERRORPROVIDER_HPP
