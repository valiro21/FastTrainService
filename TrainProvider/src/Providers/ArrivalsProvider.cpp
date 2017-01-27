//
// Created by vrosca on 1/21/17.
//

#include "ArrivalsProvider.hpp"

ArrivalsProvider::ArrivalsProvider (std::string station, std::string country, Calendar calendar) {
    query = "MATCH (tr:Trip)-[t:TO_STOP]->(a:Stop{name: '" + station + "'}), (tr:Trip)-[:FOR]->(r:Route)-[:STARTS_AT]->(b:Stop), (b)-[t2:TO_TRIP]->(tr), (tr)-[:HAS]->(s:Service) WHERE ";
    int max_day = 3;
    for (int day = 0; day < max_day; day++) {
        std::string dayName = calendar.getDayName();
        std::string time = std::to_string(calendar.getDayTimeUnix() + day * 60 * 60 * 24);

        query += "(t.arrival >= " + time + " AND s." + dayName + " = '1') ";
        if (day < max_day - 1) {
            query += "OR ";
        }
        else {
            query += "RETURN r, b, t, tr;";
        }
        calendar.add(-1, Calendar::DAY);
    }
    type = "ArrivalsProvider";
}

json ArrivalsProvider::provide (neo4j_result_stream_t * result_stream) {
    neo4j_result_t *result = neo4j_fetch_next(result_stream);
    json json_response;
    std::vector<json> pieces;

    while (result != NULL) {
        json json_response_piece;
        json route = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        json origin = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 1))["properties"];
        json edge = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 2))["properties"];
        json trip = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 3))["properties"];

        json_response_piece["route"] = route;
        json_response_piece["origin"] = origin;
        json_response_piece["arrival"] = edge["arrival"];
        json_response_piece["delay"] = trip["delay"];
        json_response_piece["trip_id"] = trip["id"];

        pieces.push_back(json_response_piece);
        result = neo4j_fetch_next(result_stream);
    }

    json_response = json(pieces);
    pieces.clear();
    return json_response;
}