//
// Created by vrosca on 1/10/17.
//

#include <QtWidgets/QLineEdit>
#include <QLabel>
#include <QtWidgets/QVBoxLayout>
#include "ActionSelector.hpp"
#include "CitySelector.hpp"

QVBoxLayout* createCityLayout (std::string label, QLineEdit *city) {
    QLabel *cityl = new QLabel();
    city = new CitySelector ();
    cityl->setText(label.c_str());

    QVBoxLayout *infoLayout = new QVBoxLayout();

    infoLayout->addWidget(cityl);
    infoLayout->addWidget(city);

    return infoLayout;
}

ActionSelector::ActionSelector (QWidget *parent) : QTabWidget(parent){
    QWidget *infoWidgetArrivals = new QWidget();
    QWidget *infoWidgetDepartures = new QWidget();

    infoWidgetArrivals->setLayout(createCityLayout("City:", arrivals_city));
    infoWidgetArrivals->setFixedHeight(100);
    infoWidgetDepartures->setLayout(createCityLayout("City", departures_city));
    infoWidgetDepartures->setFixedHeight(100);

    QWidget *pathWidget1 = new QWidget ();
    QWidget *pathWidget2 = new QWidget ();
    QWidget *pathWidget = new QWidget ();
    pathWidget1->setLayout(createCityLayout("Origin:", start_city_path));
    pathWidget2->setLayout(createCityLayout("Destination:", start_city_path));
    pathWidget->setLayout([pathWidget1, pathWidget2](){
        QVBoxLayout *infoLayout = new QVBoxLayout();

        infoLayout->addWidget(pathWidget1);
        infoLayout->addWidget(pathWidget2);

        return infoLayout;
    }());
    pathWidget1->setFixedHeight(100);
    pathWidget2->setFixedHeight(100);
    pathWidget->setFixedHeight(200);

    addTab(infoWidgetDepartures, "Departures");
    addTab(infoWidgetArrivals, "Arrivals");
    addTab(pathWidget, "Route");
    QObject::connect(this, SIGNAL(currentChanged (int)), this, SLOT (currentTabChanged(int)));
}

ActionSelector * ActionSelector::instance = nullptr;
ActionSelector& ActionSelector::GetInstance (QWidget *parent) {
    if (instance == nullptr) {
        instance = new ActionSelector(parent);
    }
    return *instance;
}

std::string ActionSelector::getArrivalCity () {
    if (getCurrentTab () == 1)
        return arrivals_city->text().toStdString();
    else {
        return start_city_path->text ().toStdString ();
    }
}

std::string ActionSelector::getDestinationCity () {
    if (getCurrentTab () == 1)
        return departures_city->text().toStdString();
    else {
        return destination_city_path->text ().toStdString ();
    }
}

int ActionSelector::getCurrentTab () {
    return tab;
}

void ActionSelector::currentTabChanged(int t) {
    tab = t;
}