//
// Created by vrosca on 1/19/17.
//

#ifndef FASTTRAINSERVICE_DATABASEUTILS_HPP
#define FASTTRAINSERVICE_DATABASEUTILS_HPP


#include <neo4j-client.h>
#include <string>
#include "../../Utils/include/json/json.hpp"

using json = nlohmann::json;

/** Provides utilities and requests
 */
class DatabaseUtils {
    static DatabaseUtils* singleton;
public:
    static DatabaseUtils& GetInstance ();

    std::string neo4j_raw_string (neo4j_value_t value);
    std::string neo4j_get_string (neo4j_value_t value);
    json neo4j_to_json (neo4j_value_t value);

    int getId (std::string name); /// Returns id of station
    json getStopById (int id); /// Returns a station in json format by name
    json getRouteByTripId (std::string id); /// Returns a route given a train id
    int getDepartureByStopAndTrip (int id, std::string trip_id); /// Gets departure time for a train in a station

    int getArrivalByStopAndTrip (int id, std::string trip_id); /// Gets arrival time for a train in a station
};


#endif //FASTTRAINSERVICE_DATABASEUTILS_HPP
