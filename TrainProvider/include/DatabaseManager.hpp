//
// Created by vrosca on 12/22/16.
//

#ifndef MERSULTRENURILOR_DATABASEMASTER_H
#define MERSULTRENURILOR_DATABASEMASTER_H

#include <neo4j-client.h>
#include <string>
#include <errno.h>
#include <functional>
#include <ScheduleThread.hpp>
#include <iostream>
/** Main controller for the database.
 * Ensures safe query and initialisation.
 */
class DatabaseManager {
    static std::string user, pass;
    static std::string connection_string;
    static neo4j_connection_t *connection;
    static DatabaseManager* instance;
public:
    static std::string default_hostname;
    static int default_port;
    static DatabaseManager& GetInstance ();
    int init (std::string host = "", int port = 0);
    void query (std::string queryStr, std::function<void(neo4j_result_stream_t*)> process_data) throw(std::ios_base::failure);
    ScheduleThread *delay_manager_thread;
    void startDelayManager ();
};


#endif //MERSULTRENURILOR_DATABASEMASTER_H
