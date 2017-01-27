//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_UPDATEDELAY_HPP
#define FASTTRAINSERVICE_UPDATEDELAY_HPP


#include <neo4j-client.h>
#include "SingleQueryProvider.hpp"
/** Updates delay for a given request
 */
class UpdateDelay : public SingleQueryProvider {
public:
    json provide (neo4j_result_stream_t *stream);
    UpdateDelay (std::vector<std::string> trips);
    std::vector<std::string> trips;
};

#endif //FASTTRAINSERVICE_UPDATEDELAY_HPP
