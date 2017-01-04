//
// Created by vrosca on 12/22/16.
//

#ifndef MERSULTRENURILOR_DATABASEMASTER_H
#define MERSULTRENURILOR_DATABASEMASTER_H

#include <neo4j-client.h>
#include <string>
#include <errno.h>
#include <functional>

class DatabaseManager {
    static std::string user, pass;
    static std::string addr, port;
    static std::string connection_string;
    static neo4j_connection_t *connection;

public:
    static int initDB ();
    static int query (std::string queryStr, std::function<void(neo4j_result_stream_t*)> process_data);
};


#endif //MERSULTRENURILOR_DATABASEMASTER_H
