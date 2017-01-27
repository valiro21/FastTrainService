//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_SQPROVIDER_HPP
#define FASTTRAINSERVICE_SQPROVIDER_HPP

#include <json/json.hpp>
#include <string>
#include <DatabaseManager.hpp>
#include <vector>
#include <DatabaseUtils.hpp>
#include <Logger.hpp>
#include "Provider.hpp"

using json = nlohmann::json;
/** Interface for requests that need a single query to complete.
 * Provides internal error handling
 */
class SingleQueryProvider : public Provider {
protected:
    std::string query;
    virtual json provide(neo4j_result_stream_t *result_stream) {
        return json ();
    }
public:
    std::string type;
    json execute ();
};


#endif //FASTTRAINSERVICE_SQPROVIDER_HPP
