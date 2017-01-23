//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_PROVIDERFACTORY_HPP
#define FASTTRAINSERVICE_PROVIDERFACTORY_HPP


#include "Provider.hpp"
#include <json/json.hpp>

class ProviderFactory {
private:
    static ProviderFactory* instance;
public:
    Provider* produce (json);
    static ProviderFactory& GetInstance();
};


#endif //FASTTRAINSERVICE_PROVIDERFACTORY_HPP
