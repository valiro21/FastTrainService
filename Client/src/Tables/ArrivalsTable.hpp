//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_ARRIVALSTABLE_HPP
#define FASTTRAINSERVICE_ARRIVALSTABLE_HPP

#include "RoutesTable.hpp"

class ArrivalsTable : public RoutesTable {
public:
    ArrivalsTable(QWidget *parent = 0);
    void setHeader ();
    void feed (json data);
};


#endif //FASTTRAINSERVICE_ARRIVALSTABLE_HPP
