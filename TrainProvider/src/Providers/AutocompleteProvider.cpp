//
// Created by vrosca on 1/21/17.
//

#include <Utils.hpp>
#include "AutocompleteProvider.hpp"

AutocompleteProvider::AutocompleteProvider (std::string prefix, float geo_lat, float geo_lng) {
    std::string lat = std::to_string(geo_lat);
    std::string lng = std::to_string(geo_lng);

    std::string better_prefix = Utils::GetInstance().diacritics_fix (prefix);


    query = "MATCH (a:Stop) WHERE a.name =~ '" + better_prefix + ".*' "
                        + "RETURN a ORDER BY (toFloat(" + lng + ") - toFloat(a.lng))^2 + (toFloat(" + lat + ") - toFloat(a.lat))^2 asc LIMIT 20;";
    type = "AutocompleteProvider";
}

json AutocompleteProvider::provide (neo4j_result_stream_t *stream) {
    neo4j_result_t *result = neo4j_fetch_next(stream);
    json json_response;

    std::vector<json> word_result;
    while (result != NULL) {
        json station = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];

        json json_piece = json();
        json_piece = station;

        word_result.push_back (json_piece);
        result = neo4j_fetch_next(stream);
    }
    json_response = json(word_result);

    return json_response;
}