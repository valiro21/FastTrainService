//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP
#define FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP

#include "Provider.hpp"

class DeparturesProvider : public Provider {
public:
    json provide (neo4j_result_stream_t * result_stream);
    DeparturesProvider (std::string station, std::string city, std::string country, long long time);
};


#endif //FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP
