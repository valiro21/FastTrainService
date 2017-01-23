//
// Created by vrosca on 12/22/16.
//

#include <vector>
#include "../include/DatabaseManager.hpp"

std::string DatabaseManager::user = "neo4j";
std::string DatabaseManager::pass = "train1234";
#ifdef RELEASE
std::string DatabaseManager::default_hostname = "db";
#else
std::string DatabaseManager::default_hostname = "localhost";
#endif
int DatabaseManager::default_port = 7687;
std::string DatabaseManager::connection_string = "";
neo4j_connection_t* DatabaseManager::connection= NULL;

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager& DatabaseManager::GetInstance () {
    if (instance == nullptr)
        instance = new DatabaseManager();
    return *instance;
}

int DatabaseManager::init(std::string hostname, int port) {
    int db_port = port ? port : DatabaseManager::default_port;
    std::string db_hostname = DatabaseManager::default_hostname;
    if (hostname != "") db_hostname = hostname;

    DatabaseManager::connection_string = "neo4j://" +
                                            DatabaseManager::user + ":" +
                                            DatabaseManager::pass + "@" +
                                            db_hostname + ":" +
                                            std::to_string(db_port);
    neo4j_client_init();

    return EXIT_SUCCESS;
}

int DatabaseManager::query (std::string queryStr, std::function<void(neo4j_result_stream_t*)> process_data) {
    DatabaseManager::connection =
            neo4j_connect(DatabaseManager::connection_string.c_str(), NULL, NEO4J_INSECURE);

    if (connection == NULL) {
        neo4j_perror(stderr, errno, "Connection failed");
        return EXIT_FAILURE;
    }

    neo4j_session_t *session = neo4j_new_session(DatabaseManager::connection);
    if (session == NULL) {
        neo4j_perror(stderr, errno, "Failed to start session");
        return EXIT_FAILURE;
    }

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
    neo4j_reset_session(session);
    neo4j_end_session(session);
    neo4j_close(DatabaseManager::connection);

    return EXIT_SUCCESS;
}