//
// Created by vrosca on 1/19/17.
//

#include <Logger.hpp>
#include <DatabaseManager.hpp>
#include "Utils.hpp"
#include "DatabaseUtils.hpp"
DatabaseUtils* DatabaseUtils::singleton = NULL;

DatabaseUtils& DatabaseUtils::GetInstance () {
    if (singleton == nullptr) {
        singleton = new DatabaseUtils();
    }
    return *singleton;
}

std::string DatabaseUtils::neo4j_raw_string (neo4j_value_t value) {
    char *buf = new char[2048];
    size_t nr;
    if ((nr = neo4j_ntostring(value, buf, 2048)) > 2048) {
        delete[] buf;
        buf = new char[nr+2];
        neo4j_ntostring(value, buf, 2048);
    }

    std::string result = buf;
    delete[] buf;

    return result;
}

std::string DatabaseUtils::neo4j_get_string (neo4j_value_t value) {
    char *buf = new char[2048];
    size_t nr;
    if ((nr = neo4j_ntostring(value, buf, 2048)) > 2048) {
        delete[] buf;
        buf = new char[nr+2];
        neo4j_ntostring(value, buf, 2048);
    }

    std::string result;
    if (buf[0] == '"') {
        result = std::string (buf + 1);
    }
    else {
        result = buf;
    }
    delete[] buf;
    if (result.back() == '"') result.pop_back();

    return result;
}

json DatabaseUtils::neo4j_to_json (neo4j_value_t value) {
    if (neo4j_type(value) == NEO4J_NODE) {
        neo4j_value_t value1 = neo4j_node_labels(value),
                value2 = neo4j_node_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value2))));
        return result;
    }
    else if (neo4j_type(value)) {
        neo4j_value_t value1 = neo4j_relationship_type(value),
                value2 = neo4j_relationship_properties(value);
        json result;
        result.emplace ("types", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value1))));
        result.emplace ("properties", json::parse(Utils::GetInstance().repair_json_string(DatabaseUtils::neo4j_raw_string(value2))));

        return result;
    }
    else {
        return json();
    }
}

int DatabaseUtils::getId (std::string name) {
    std::string query = "MATCH (a:Stop{name: '" + name +"'}) RETURN a;";
    int id;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        while (result != NULL) {
            json station = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];

            id = std::stoi(station["id"].get<std::string>());
            return;
        }
        id = -1;
    });
    return id;
}

json DatabaseUtils::getStopById (int id) {
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) +"'}) RETURN a;";
    json stop;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            stop = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        }
        else {
            stop = json();
        }
    });
    return stop;
}

json DatabaseUtils::getRouteByTripId (std::string id) {
    Logger::GetInstance().logd(id);
    std::string query = "MATCH (tr:Trip{id: '" + id +"'})-[:FOR]->(r:Route) RETURN r;";
    json route;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            route = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
        }
        else {
            route = json();
        }
    });
    return route;
}

int DatabaseUtils::getDepartureByStopAndTrip (int id, std::string trip_id) {
    std::string query = "MATCH (a:Stop{id: '" + std::to_string(id) + "'})-[t:TO_TRIP]->(tr:Trip{id: '" + trip_id +"'}) RETURN t;";
    int departure;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            json to_trip = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
            departure = to_trip["departure"];
        }
        else {
            departure = -1;
        }
    });
    return departure;
}

int DatabaseUtils::getArrivalByStopAndTrip (int id, std::string trip_id) {
    std::string query = "MATCH (tr:Trip{id: '" + trip_id +"'})-[t:TO_STOP]->(a:Stop{id: '" + std::to_string(id) + "'}) RETURN t;";
    int arrival;
    DatabaseManager::GetInstance().query(query,[&](neo4j_result_stream_t *result_stream){
        neo4j_result_t *result = neo4j_fetch_next(result_stream);

        if (result != NULL) {
            json to_stop = DatabaseUtils::GetInstance().neo4j_to_json(neo4j_result_field(result, 0))["properties"];
            arrival = to_stop["arrival"];
        }
        else {
            arrival = -1;
        }
    });
    return arrival;
}