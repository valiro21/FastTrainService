//
// Created by vrosca on 1/21/17.
//

#include "ArrivalsProvider.hpp"

ArrivalsProvider::ArrivalsProvider (std::string station, std::string country, Calendar calendar) {
    std::string dayName = calendar.getDayName();
    query = "MATCH (tr:Trip)-[t:TO_STOP]->(a:Stop{name: '" + station + "'}), (tr:Trip)-[:FOR]->(r:Route)-[:STARTS_AT]->(b:Stop), (tr)-[:HAS]->(s:Service{"
            + dayName +": '1'}) RETURN r, b, t, tr;";
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

        pieces.push_back(json_response_piece);
        result = neo4j_fetch_next(result_stream);
    }

    json_response = json(pieces);
    pieces.clear();
    return json_response;
}