//
// Created by vrosca on 12/22/16.
//

#include "RequestTaskFactory.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "ArrivalsRequest.hpp"
#include "DeparturesRequest.hpp"

RequestTaskFactory* RequestTaskFactory::singleton = NULL;

RequestTaskFactory& RequestTaskFactory::GetInstance() {
    if (singleton == NULL) {
        singleton = new RequestTaskFactory();
    }
    return *singleton;
}


RequestTask* RequestTaskFactory::getTask (json request) throw (std::domain_error){
    RequestTask *task;
    std::string action = request["action"].get<std::string>();
    if (action == "arrivals")
        return new ArrivalsRequest ();
    else if (action == "departures")
        return new DeparturesRequest ();
    else
        throw std::ios_base::failure("Field action missing from request");
    return NULL;
}