//
// Created by vrosca on 1/26/17.
//

#include "UpdateDelay.hpp"
UpdateDelay::UpdateDelay (std::vector<std::string> trips) {
    query = "MATCH (tr:Trip) WHERE ";
    for (auto id : trips) {
        query += "tr.id = '" + id + "'";
        if (id != trips.back ()) {
            query += " OR ";
        }
        else {
            query += " RETURN tr.delay, tr.id;";
        }
    }

    this->trips = trips;
}

json UpdateDelay::provide (neo4j_result_stream_t *stream) {
    json json_response;

    neo4j_result_t *result = neo4j_fetch_next(stream);

    std::vector<json> json_total (trips.size (), json ());
    while (result != NULL) {
        int delay = (int) neo4j_int_value(neo4j_result_field(result, 0));
        json trip_id = DatabaseUtils::GetInstance().neo4j_get_string(neo4j_result_field(result, 1));

        json json_piece = json();
        for (int i = 0; i < trips.size (); i++) {
            if (trips[i] == trip_id) {
                json_total[i]["trip_id"] = trip_id;
                json_total[i]["delay"] = delay;
            }
        }

        result = neo4j_fetch_next(stream);
    }
    return json_total;
}