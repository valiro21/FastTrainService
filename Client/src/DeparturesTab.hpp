//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_DEPARTURESTAB_HPP
#define FASTTRAINSERVICE_DEPARTURESTAB_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "Tables/DeparturesTable.hpp"
#include "CitySelector.hpp"
#include "DateSelector.hpp"
#include "Tables/RoutesTable.hpp"

class DeparturesTab : public QWidget {
Q_OBJECT
    CitySelector *citySelector;
    QPushButton* searchButton;
    DateSelector *dateSelector;
    DeparturesTable* routeInfo;
public:
    DeparturesTab (QWidget *parent = 0);

private slots:
    void search(bool checked = false);
};


#endif //FASTTRAINSERVICE_DEPARTURESTAB_HPP
