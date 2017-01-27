//
// Created by vrosca on 12/22/16.
//

#include <vector>
#include <bits/ios_base.h>
#include <Calendar.hpp>
#include <Provider.hpp>
#include "../include/DatabaseManager.hpp"
#include "Providers/DelayResetProvider.hpp"

std::string DatabaseManager::user = "neo4j";
std::string DatabaseManager::pass = "train12345";
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
    Logger::GetInstance().logd("Connecting to database on " + db_hostname + ":" + std::to_string(db_port));
    neo4j_client_init();

    auto connection = neo4j_connect(DatabaseManager::connection_string.c_str(), NULL, NEO4J_INSECURE);
    if (connection == NULL)
        return EXIT_FAILURE;
    else
        neo4j_close(connection);

    return EXIT_SUCCESS;
}

void DatabaseManager::query (std::string queryStr, std::function<void(neo4j_result_stream_t*)> process_data) throw(std::ios_base::failure) {
    DatabaseManager::connection =
            neo4j_connect(DatabaseManager::connection_string.c_str(), NULL, NEO4J_INSECURE);

    if (connection == NULL) {
        char buf[1024];
        throw std::ios_base::failure(std::string("Connection failed: ") + neo4j_strerror(errno, buf, sizeof(buf)));
    }

    neo4j_session_t *session = neo4j_new_session(DatabaseManager::connection);
    if (session == NULL) {
        char buf[1024];

        throw std::ios_base::failure(std::string("Failed to start session: ") + neo4j_strerror(errno, buf, sizeof(buf)));
    }

    neo4j_result_stream_t *results = neo4j_run (session, queryStr.c_str(), neo4j_null);

    if (results == NULL) {
        char buf[1024];
        throw std::ios_base::failure(std::string("Failed to run statement: ") + neo4j_strerror(errno, buf, sizeof(buf)));
    }

    process_data(results);

    neo4j_close_results(results);
    neo4j_reset_session(session);
    neo4j_end_session(session);
    neo4j_close(DatabaseManager::connection);
}

void DatabaseManager::startDelayManager () {
    delay_manager_thread = new ScheduleThread([&](){
        Provider *provider = new DelayResetProvider(Calendar());
        provider->execute();
    }, 10000, 600000);
    delay_manager_thread->start();
}