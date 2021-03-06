//
// Created by vrosca on 1/21/17.
//

#ifndef FASTTRAINSERVICE_PROVIDERFACTORY_HPP
#define FASTTRAINSERVICE_PROVIDERFACTORY_HPP

#include "Provider.hpp"
#include <json/json.hpp>
/** Given a request, it decides what request provider to use.
 */
class ProviderFactory {
private:
    static ProviderFactory* instance;
public:
    Provider* produce (json request);
    static ProviderFactory& GetInstance();
};


#endif //FASTTRAINSERVICE_PROVIDERFACTORY_HPP
