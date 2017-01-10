//
// Created by vrosca on 1/10/17.
//

#include <Utils.hpp>
#include <Logger.hpp>
#include "AutocompleteRequest.hpp"
#include "DatabaseManager.h"

std::string AutocompleteRequest::solve (json request) {
    std::string geo_long = std::to_string(request["longitude"].get<int>());
    std::string geo_lat = std::to_string(request["latitude"].get<int>());

    std::string query = "MATCH (a:Station) WHERE a.city LIKE '" + request["prefix"].get<std::string>() + "' "
     + "RETURN a ORDER BY (" + geo_long + "- a.longitude)^2 + (" + geo_lat + " - a.latitude)^2 asc LIMIT 5";

    std::string response;
    DatabaseManager::query(query, [&](neo4j_result_stream_t *stream){
        neo4j_result_t *result = neo4j_fetch_next(stream);
        json json_response;

        try {
            std::vector<std::string> word_result;
            while (result != NULL) {
                json station = Utils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];

                std::string str_city = station["city"].get<std::string>();
                std::string str_station = station["station"].get<std::string>();

                word_result.push_back (str_city + ", " + str_station);
            }
            json_response["word"] = json (word_result);
        }
        catch (std::domain_error &e) {
            Logger::GetInstance().loge("AutocompleteRequest - Invalid request to database");
            Logger::GetInstance().loge(e.what());
            json_response = json();
        }
        catch (std::exception *e) {
            Logger::GetInstance().loge("Invalid database!");
            Logger::GetInstance().loge(e->what());
            json_response = json();
        }
        response = json_response.dump();
    });

    return response;
}