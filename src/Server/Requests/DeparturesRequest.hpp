//
// Created by vrosca on 12/23/16.
//

#ifndef MERSULTRENURILOR_DEPARTURESREQUEST_H
#define MERSULTRENURILOR_DEPARTURESREQUEST_H


#include "RequestTask.hpp"

class DeparturesRequest : public RequestTask {
    std::string solve (json request);
};


#endif //MERSULTRENURILOR_DEPARTURESREQUEST_H
