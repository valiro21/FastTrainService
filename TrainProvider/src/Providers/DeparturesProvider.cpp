//
// Created by vrosca on 1/21/17.
//

#include "DeparturesProvider.hpp"

DeparturesProvider::DeparturesProvider (std::string station, std::string country, Calendar calendar) {
    std::string dayName = calendar.getDayName();
    query = "MATCH (a:Stop{name: '" + station+ "'})-[t:TO_TRIP]->(tr:Trip)-[:FOR]->(r:Route)-[:ENDS_AT]->(b:Stop), (tr)-[:HAS]->(s:Service{"
        + dayName +": '1'}) RETURN r, b, t, tr;";
}

json DeparturesProvider::provide (neo4j_result_stream_t * result_stream) {
    neo4j_result_t *result = neo4j_fetch_next(result_stream);
    json json_response;
    std::vector<json> pieces;

    while (result != NULL) {
        json json_response_piece;
        json route = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        json endpoint = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 1))["properties"];
        json edge = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 2))["properties"];
        json trip = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 3))["properties"];

        json_response_piece["route"] = route;
        json_response_piece["endpoint"] = endpoint;
        json_response_piece["departure"] = edge["departure"];
        json_response_piece["delay"] = trip["delay"];

        pieces.push_back(json_response_piece);
        result = neo4j_fetch_next(result_stream);
    }

    json_response = json(pieces);
    pieces.clear();
    return json_response;
}