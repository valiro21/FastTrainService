//
// Created by vrosca on 1/21/17.
//

#include "Provider.hpp"

json Provider::execute () {
    json json_result;
    DatabaseManager::GetInstance().query(query, [&](neo4j_result_stream_t *stream) {
        try {
            json_result = provide (stream);

            if (json_result.find("status") == json_result.end())
               json_result["status"] = "OK";
        }
        catch (std::domain_error &e) {
            Logger::GetInstance().loge("Invalid request to database");
            Logger::GetInstance().loge(e.what());
            json_result = json();
            json_result["status"] = "ERROR";
            json_result["error"] = "Invalid request to database";
        }
        catch (std::invalid_argument &e) {
            Logger::GetInstance().logd ("Missing database field");
            Logger::GetInstance().logd(std::string(e.what()));
            json_result = json();
            json_result["status"] = "ERROR";
            json_result["error"] = "Missing database field";
        }
        catch (std::exception *e) {
            Logger::GetInstance().loge("Invalid database!");
            Logger::GetInstance().loge(e->what());
            json_result = json();
            json_result["status"] = "ERROR";
            json_result["error"] = "Invalid database";
        }
    });
    return json_result;
}