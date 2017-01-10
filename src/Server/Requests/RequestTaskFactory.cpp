//
// Created by vrosca on 12/22/16.
//

#include "RequestTaskFactory.hpp"
#include "Utils.hpp"
#include "Server/Requests/ArrivalsRequest.hpp"
#include "Server/Requests/DeparturesRequest.hpp"
#include "Server/Requests/AutocompleteRequest.hpp"

RequestTaskFactory* RequestTaskFactory::singleton = NULL;

RequestTaskFactory& RequestTaskFactory::GetInstance() {
    if (singleton == NULL) {
        singleton = new RequestTaskFactory();
    }
    return *singleton;
}


RequestTask* RequestTaskFactory::getTask (json request) throw (std::domain_error){
    std::string action = request["action"].get<std::string>();
    if (action == "arrivals")
        return new ArrivalsRequest ();
    else if (action == "departures")
        return new DeparturesRequest ();
    else if (action == "autocomplete")
        return new AutocompleteRequest ();
    else
        throw std::ios_base::failure("Field action missing from request");
    return NULL;
}