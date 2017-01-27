//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP
#define FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP

#include "SingleQueryProvider.hpp"
#include <Calendar.hpp>

/** Returns trains that will depart after a given time at the given station
 */
class DeparturesProvider : public SingleQueryProvider {
public:
    json provide (neo4j_result_stream_t * result_stream);
    DeparturesProvider (std::string station, std::string country, Calendar calendar);
};


#endif //FASTTRAINSERVICE_DEPARTURESPROVIDER_HPP
