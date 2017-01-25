//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_DEPARTURESTABLE_HPP
#define FASTTRAINSERVICE_DEPARTURESTABLE_HPP


#include "RoutesTable.hpp"

class DeparturesTable : public RoutesTable {
public:
    void setHeader ();
    DeparturesTable(QWidget *parent = 0);
    void feed (json data);
};


#endif //FASTTRAINSERVICE_DEPARTURESTABLE_HPP
