//
// Created by vrosca on 1/21/17.
//

#include "SingleQueryProvider.hpp"

json SingleQueryProvider::execute () {
    json json_result;
    try {
        DatabaseManager::GetInstance().query(query, [&](neo4j_result_stream_t *stream) {
            try {
                json result = provide(stream);
                if (result.find("ERROR") == result.end ()) {
                    json_result["RESULT"] = result;
                    json_result["STATUS"] = "OK";
                }
                else {
                    result["STATUS"] = "ERROR";
                    json_result = result;
                }
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
        return json_result;
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