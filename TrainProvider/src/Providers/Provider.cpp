//
// Created by vrosca on 1/21/17.
//

#include "Provider.hpp"

json Provider::execute () {
    json json_result;
    try {
        DatabaseManager::GetInstance().query(query, [&](neo4j_result_stream_t *stream) {
            try {
                json_result["RESULT"] = provide(stream);
                json_result["STATUS"] = "OK";
            }
            catch (std::domain_error &e) {
                Logger::GetInstance().loge("Invalid request to database");
                Logger::GetInstance().loge(e.what());
                json_result = json();
                json_result["STATUS"] = "ERROR";
                json_result["ERROR"] = "Invalid request to database";
            }
            catch (std::invalid_argument &e) {
                Logger::GetInstance().logd("Missing database field");
                Logger::GetInstance().logd(std::string(e.what()));
                json_result = json();
                json_result["STATUS"] = "ERROR";
                json_result["ERROR"] = "Missing database field";
            }
            catch (std::exception *e) {
                Logger::GetInstance().loge("Invalid database!");
                Logger::GetInstance().loge(e->what());
                json_result = json();
                json_result["STATUS"] = "ERROR";
                json_result["ERROR"] = "Invalid database";
            }
        });
    }
    catch (std::ios_base::failure &e) {
        Logger::GetInstance().logd ("DB connection problem");
        Logger::GetInstance().logd (std::string(e.what()));
        json_result = json();
        json_result["STATUS"] = "ERROR";
        json_result["ERROR"] = "Could not fetch data from database";
    }
    return json_result;
}