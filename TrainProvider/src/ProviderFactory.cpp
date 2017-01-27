//
// Created by vrosca on 1/21/17.
//

#include "ProviderFactory.hpp"
#include "Providers/ArrivalsProvider.hpp"
#include "Providers/DeparturesProvider.hpp"
#include "Providers/AutocompleteProvider.hpp"
#include "Providers/ErrorProvider.hpp"
#include "Providers/ShortestPathProvider.hpp"
#include "Providers/UpdateProvider.hpp"
#include "Providers/UpdateDelay.hpp"

ProviderFactory* ProviderFactory::instance = nullptr;

ProviderFactory& ProviderFactory::GetInstance() {
    if (instance == nullptr) {
        instance = new ProviderFactory();
    }
    return *instance;
}

Provider* ProviderFactory::produce (json request) {
    try {
        std::string action = request["action"].get<std::string>();
        if (action == "arrivals")
            return new ArrivalsProvider(
                    request["station"].get<std::string>(),
                    request["country"].get<std::string>(),
                    Calendar::fromJSON(request["time"]));
        else if (action == "departures")
            return new DeparturesProvider(
                    request["station"].get<std::string>(),
                    request["country"].get<std::string>(),
                    Calendar::fromJSON(request["time"]));
        else if (action == "autocomplete")
            return new AutocompleteProvider(
                    request["prefix"].get<std::string>(),
                    request["lat"],
                    request["lng"]);
        else if (action == "update")
            return new UpdateProvider (
                    request["minute"].get<int>(),
                    request["trip_id"].get<std::string>());
        else if (action == "update_delay") {
            return new UpdateDelay (request["trips"].get<std::vector<std::string> >());
        }
        else if (action == "path")
            return new ShortestPathProvider (request);
        else
            return new ErrorProvider("Field action missing from request");
    }
    catch (std::domain_error &e) {
        Logger::GetInstance().loge("Invalid request to database");
        Logger::GetInstance().loge(e.what());
        return new ErrorProvider ("The request is missing field");
    }
}