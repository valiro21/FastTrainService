//
// Created by vrosca on 1/26/17.
//

#include "UpdateProvider.hpp"

UpdateProvider::UpdateProvider (int minutes, std::string trip_id) {
    query = "MATCH (tr:Trip{id: '" + trip_id + "'}) SET tr.delay = tr.delay + " + std::to_string(minutes) + ";";
    type = "UpdateProvider";
}

json UpdateProvider::provide (neo4j_result_stream_t *stream) {
    json json_response;
    json_response = "OK";
    return json_response;
}