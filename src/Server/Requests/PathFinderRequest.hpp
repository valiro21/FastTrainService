//
// Created by vrosca on 12/23/16.
//

#ifndef MERSULTRENURILOR_PATHFINDERREQUEST_H
#define MERSULTRENURILOR_PATHFINDERREQUEST_H


#include "RequestTask.hpp"

class PathFinderRequest : public RequestTask {
    std::string solve (json request);
};


#endif //MERSULTRENURILOR_PATHFINDERREQUEST_H
