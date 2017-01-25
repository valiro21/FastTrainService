//
// Created by vrosca on 1/21/17.
//

#include "ErrorProvider.hpp"

ErrorProvider::ErrorProvider (std::string message) {
    response = json ();
    response["STATUS"] = "ERROR";
    response["ERROR"] = message;
    type = "ErrorProvider";
}

json ErrorProvider::provide(neo4j_result_stream_t *result_stream) {
    return response;
}