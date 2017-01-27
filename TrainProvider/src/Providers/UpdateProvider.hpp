//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_UPDATEPROVIDER_HPP
#define FASTTRAINSERVICE_UPDATEPROVIDER_HPP

#include <neo4j-client.h>
#include "SingleQueryProvider.hpp"
/** Provides update for delays to refresh on the client.
 */
class UpdateProvider : public SingleQueryProvider {
public:
    json provide (neo4j_result_stream_t *stream);
    UpdateProvider (int minutes, std::string trip_id);
};


#endif //FASTTRAINSERVICE_UPDATEPROVIDER_HPP
