//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_PATHSTABLE_HPP
#define FASTTRAINSERVICE_PATHSTABLE_HPP


#include "RoutesTable.hpp"

class PathsTable : public RoutesTable {
public:
    void setHeader ();
    PathsTable(QWidget *parent = 0);
    void feed (json data);
};


#endif //FASTTRAINSERVICE_PATHSTABLE_HPP
