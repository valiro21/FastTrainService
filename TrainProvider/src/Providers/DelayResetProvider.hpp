//
// Created by vrosca on 1/27/17.
//

#ifndef FASTTRAINSERVICE_DELAYRESETPROVIDER_HPP
#define FASTTRAINSERVICE_DELAYRESETPROVIDER_HPP


#include "SingleQueryProvider.hpp"
#include <Calendar.hpp>
/** Resets delay for trains that already arrived at a station.
 */
class DelayResetProvider : public SingleQueryProvider {
public:
    json provide (neo4j_result_stream_t * result_stream);
    DelayResetProvider (Calendar time);
};


#endif //FASTTRAINSERVICE_DELAYRESETPROVIDER_HPP
