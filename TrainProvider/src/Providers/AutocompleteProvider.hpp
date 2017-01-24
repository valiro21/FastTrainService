#include <neo4j-client.h>
#include "Provider.hpp"

// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_AUTOCOMPLETEPROVIDER_HPP
#define FASTTRAINSERVICE_AUTOCOMPLETEPROVIDER_HPP


class AutocompleteProvider : public Provider {
public:
    json provide (neo4j_result_stream_t *stream);
    AutocompleteProvider (std::string prefix, float geo_lat, float geo_lng);
};


#endif //FASTTRAINSERVICE_AUTOCOMPLETEPROVIDER_HPP
