//
// Created by vrosca on 1/27/17.
//

#include "DelayResetProvider.hpp"

DelayResetProvider::DelayResetProvider (Calendar calendar) {
    query = "MATCH (tr:Trip)-[t2:TO_STOP]->(b:Stop), (tr)-[:HAS]->(s:Service), (tr)-[:FOR]->(r:Route)-[:ENDS_AT]->(b) WHERE tr.delay > 0 AND (";
    int max_day = 3;
    for (int day = 0; day < max_day; day++) {
        std::string dayName = calendar.getDayName();
        std::string time = std::to_string(calendar.getDayTimeUnix() + day * 60 * 60 * 24);

        query += "(t2.arrival + tr.delay <= " + time + " AND s." + dayName + " = '1') ";
        if (day < max_day - 1) {
            query += "OR ";
        }
        else {
            query += ") SET tr.delay = 0;";
        }
        calendar.add(-1, Calendar::DAY);
    }
    type = "DelayResetProvider";
}

json DelayResetProvider::provide (neo4j_result_stream_t * result_stream) {
    neo4j_result_t *result = neo4j_fetch_next(result_stream);
    json json_response;
    json_response = json();
    json_response["RESULT"] = "OK";
    return json_response;
}