//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_ROUTESTAB_HPP
#define FASTTRAINSERVICE_ROUTESTAB_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "CitySelector.hpp"
#include "DateSelector.hpp"
#include "Tables/PathsTable.hpp"

class RoutesTab : public QWidget {
Q_OBJECT
    CitySelector *citySelectorStart;
    CitySelector *citySelectorEnd;
    QPushButton* searchButton;
    DateSelector *dateSelector;
    PathsTable* routeInfo;
public:
    RoutesTab (QWidget *parent = 0);

private slots:
    void search(bool checked = false);
};


#endif //FASTTRAINSERVICE_ROUTESTAB_HPP
