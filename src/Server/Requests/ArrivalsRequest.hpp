//
// Created by vrosca on 12/23/16.
//

#ifndef MERSULTRENURILOR_ARRIVALSREQUEST_H
#define MERSULTRENURILOR_ARRIVALSREQUEST_H


#include "RequestTask.hpp"

class ArrivalsRequest : public RequestTask {
    std::string solve (json request);
};


#endif //MERSULTRENURILOR_ARRIVALSREQUEST_H
