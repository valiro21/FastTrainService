//
// Created by vrosca on 1/21/17.
//

#include "AutocompleteProvider.hpp"

AutocompleteProvider::AutocompleteProvider (std::string prefix, float geo_lat, float geo_lng) {
    std::string lat = std::to_string(geo_lat);
    std::string lng = std::to_string(geo_lng);
    std::string query = "MATCH (a:Station) WHERE a.city LIKE '" + prefix + "' "
                        + "RETURN a ORDER BY (" + lng + "- a.longitude)^2 + (" + lat + " - a.latitude)^2 asc LIMIT 5";
}

json AutocompleteProvider::provide (neo4j_result_stream_t *stream) {
    neo4j_result_t *result = neo4j_fetch_next(stream);
    json json_response;

    std::vector<json> word_result;
    while (result != NULL) {
        json station = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];

        json json_piece = json();
        json_piece["station"] = station["station"].get<std::string>();
        json_piece["city"] = station["city"].get<std::string>();
        json_piece["country"] = station["country"].get<std::string>();

        word_result.push_back (json_piece);
    }
    json_response["results"] = json(word_result);

    return json_response;
}