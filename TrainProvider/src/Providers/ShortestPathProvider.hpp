//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_SHORTESTPATHPROVIDER_HPP
#define FASTTRAINSERVICE_SHORTESTPATHPROVIDER_HPP


#include "MultiQueryProvider.hpp"
/**
 * Returns routes between cities. Will try to find the fastest one while not changin trains too many times.
 */
class ShortestPathProvider : public MultiQueryProvider {
protected:
    json provide(json request);
    bool canceled;
public:
    ShortestPathProvider(json request) : MultiQueryProvider(request) {};
};


#endif //FASTTRAINSERVICE_SHORTESTPATHPROVIDER_HPP
