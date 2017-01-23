//
// Created by vrosca on 1/21/17.
//

#include "DeparturesProvider.hpp"

DeparturesProvider::DeparturesProvider (std::string station, std::string city, std::string country, long long time) {
    std::string str_time = std::to_string(time);
    query = std::string() + "MATCH (a:Station)-[t1:DEST_TO_TRAIN]->(t:Train)-[t2:TRAIN_TO_DEST]->(b:Station) WHERE "
            + "a.city='" + city + "' AND "
            + "a.station='" + station + "' "
            + "a.country='" + country + "' "
            + "t1.arrival < " + str_time + " "
            + "RETURN b, t, t2";
}

json DeparturesProvider::provide (neo4j_result_stream_t * result_stream) {
    neo4j_result_t *result = neo4j_fetch_next(result_stream);
    json json_response;
    std::vector<json> pieces;

    while (result != NULL) {
        json json_response_piece;
        json station = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        json train = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 1))["properties"];
        json to_train = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 3))["properties"];


        json_response_piece["station"] = station["station"].get<std::string>();
        json_response_piece["origin"] = train["origin"].get<std::string>();
        json_response_piece["endpoint"] = train["endpoint"].get<std::string>();
        json_response_piece["departure"] = to_train["departure"];

        pieces.push_back(json_response_piece);
        result = neo4j_fetch_next(result_stream);
    }

    json_response["result"] = json(pieces);
    pieces.clear();
    return json_response;
}