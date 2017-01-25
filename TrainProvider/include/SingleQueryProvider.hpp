//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_SQPROVIDER_HPP
#define FASTTRAINSERVICE_SQPROVIDER_HPP

#include <json/json.hpp>
#include <string>
#include <DatabaseManager.hpp>
#include <vector>
#include <DatabaseUtils.hpp>
#include <Logger.hpp>
#include "Provider.hpp"

using json = nlohmann::json;

class SingleQueryProvider : public Provider {
protected:
    std::string query;
public:
    std::string type;
    json execute ();
};


#endif //FASTTRAINSERVICE_SQPROVIDER_HPP
