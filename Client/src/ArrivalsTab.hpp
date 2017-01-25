//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_ARRIVALSTAB_HPP
#define FASTTRAINSERVICE_ARRIVALSTAB_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "Tables/ArrivalsTable.hpp"
#include "CitySelector.hpp"
#include "DateSelector.hpp"
#include "Tables/RoutesTable.hpp"

class ArrivalsTab : public QWidget {
Q_OBJECT
    CitySelector *citySelector;
    QPushButton* searchButton;
    DateSelector *dateSelector;
    ArrivalsTable* routeInfo;
public:
    ArrivalsTab (QWidget *parent = 0);

private slots:
    void search(bool checked = false);
};


#endif //FASTTRAINSERVICE_ARRIVALSTAB_HPP
