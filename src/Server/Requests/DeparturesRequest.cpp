//
// Created by vrosca on 12/23/16.
//

#include "DeparturesRequest.hpp"
#include "DatabaseManager.h"
#include "Utils.hpp"
#include "Logger.hpp"

std::string DeparturesRequest::solve (json request) {
    std::string query = "MATCH (a:Station)-[t1:DEST_TO_TRAIN]->(t:Train)-[t2:TRAIN_TO_DEST]->(b:Station) WHERE a.city='"
                        + request["city"].get<std::string>() +"' AND a.station='"
                        + request["station"].get<std::string>() + "'RETURN b, t, t1, t2";

    std::string response;
    DatabaseManager::query(query, [&](neo4j_result_stream_t *stream){
        neo4j_result_t *result = neo4j_fetch_next(stream);
        json json_response;

        try {
            while (result != NULL) {
                json station = Utils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
                json train = Utils::GetInstance().neo4j_to_json(neo4j_result_field(result, 1))["properties"];
                json to_train = Utils::GetInstance().neo4j_to_json(neo4j_result_field(result, 2))["properties"];
                json to_station = Utils::GetInstance().neo4j_to_json(neo4j_result_field(result, 3))["properties"];

                std::string str_city = station["city"].get<std::string>();
                std::string str_station = station["station"].get<std::string>();
                std::string str_train = train["name"].get<std::string>();
                long long departure = to_train["departure"];
                long long arrival = to_station["arrival"];

                json_response[(str_city + ", " + str_station)] =
                        {str_train,
                         std::to_string(departure),
                         std::to_string(arrival)
                        };
                result = neo4j_fetch_next(stream);
            }
        }
        catch (std::domain_error &e) {
            Logger::GetInstance().loge("DepartureRequest - Invalid request to database");
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