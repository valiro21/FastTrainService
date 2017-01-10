//
// Created by vrosca on 12/22/16.
//

#include <vector>
#include "DatabaseManager.h"

std::string DatabaseManager::user = "neo4j";
std::string DatabaseManager::pass = "train1234";
std::string DatabaseManager::addr = "localhost";
std::string DatabaseManager::port = "7687";
std::string DatabaseManager::connection_string = "";
neo4j_connection_t* DatabaseManager::connection= NULL;
std::vector<std::string> exists_constraints;

void init_constraints () {
    exists_constraints.push_back("(station:Station) ASSERT exists(station.city)");
    exists_constraints.push_back("(station:Station) ASSERT exists(station.station)");
    exists_constraints.push_back("(station:Station) ASSERT exists(station.longitude)");
    exists_constraints.push_back("(station:Station) ASSERT exists(station.latitude)");
    exists_constraints.push_back("(station:Station) ASSERT exists(station.country)");

    exists_constraints.push_back("(t:TRAN_TO_DEST) ASSERT exists(t.arrival)");
    exists_constraints.push_back("(t:DEST_TO_TRAIN) ASSERT exists(t.desparture)");
}


int DatabaseManager::initDB() {
    DatabaseManager::connection_string = "neo4j://" +
                                            DatabaseManager::user + ":" +
                                            DatabaseManager::pass + "@" +
                                            DatabaseManager::addr + ":" +
                                            DatabaseManager::port;
    neo4j_client_init();
    DatabaseManager::connection =
            neo4j_connect(DatabaseManager::connection_string.c_str(), NULL, NEO4J_INSECURE);

    if (connection == NULL) {
        neo4j_perror(stderr, errno, "Connection failed");
        return EXIT_FAILURE;
    }

    init_constraints();
    for (auto i : exists_constraints) {
        DatabaseManager::query("CREATE CONSTRAINT ON " + i, [](){});
    }


    return EXIT_SUCCESS;
}

int DatabaseManager::query (std::string queryStr, std::function<void(neo4j_result_stream_t*)> process_data) {
    neo4j_session_t *session = neo4j_new_session(DatabaseManager::connection);
    if (session == NULL) {
        neo4j_perror(stderr, errno, "Failed to start session");
        return EXIT_FAILURE;
    }

    neo4j_result_stream_t *results = neo4j_run (session, queryStr.c_str(), neo4j_null);

    if (results == NULL) {
        neo4j_perror(stderr, errno, "Failed to run statement");
        return EXIT_FAILURE;
    }

    process_data(results);

    neo4j_close_results(results);
    neo4j_end_session(session);

    return EXIT_SUCCESS;
}