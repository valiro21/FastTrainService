//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_AUTOCOMPLETEREQUEST_HPP
#define FASTTRAINSERVICE_AUTOCOMPLETEREQUEST_HPP
#include "RequestTask.hpp"

class AutocompleteRequest : public RequestTask {
    std::string solve (json request);
};


#endif //FASTTRAINSERVICE_AUTOCOMPLETEREQUEST_HPP
