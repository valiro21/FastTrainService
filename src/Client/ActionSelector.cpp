//
// Created by vrosca on 1/10/17.
//

#include <QtWidgets/QLineEdit>
#include <QLabel>
#include <QtWidgets/QVBoxLayout>
#include "ActionSelector.hpp"
#include "CitySelector.hpp"

QVBoxLayout* createCityLayout () {
    QLabel *city = new QLabel();
    CitySelector *origin_city = new CitySelector ();
    city->setText("City:");

    QVBoxLayout *infoLayout = new QVBoxLayout();

    infoLayout->addWidget(city);
    infoLayout->addWidget(origin_city);

    return infoLayout;
}

ActionSelector::ActionSelector (QWidget *parent) : QTabWidget(parent){
    QWidget *infoWidgetArrivals = new QWidget();
    QWidget *infoWidgetDepartures = new QWidget();

    infoWidgetArrivals->setLayout(createCityLayout());
    infoWidgetArrivals->setFixedHeight(100);
    infoWidgetDepartures->setLayout(createCityLayout());
    infoWidgetDepartures->setFixedHeight(100);

    addTab(infoWidgetDepartures, "Departures");
    addTab(infoWidgetArrivals, "Arrivals");
}