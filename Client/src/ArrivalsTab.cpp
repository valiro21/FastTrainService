//
// Created by vrosca on 1/25/17.
//

#include <QtWidgets/QHBoxLayout>
#include <Logger.hpp>
#include "Client.hpp"
#include "ArrivalsTab.hpp"
#include "WidgetFactory.hpp"

ArrivalsTab::ArrivalsTab (QWidget *parent) : QWidget(parent) {
    QLayout *layout = new QHBoxLayout ();

    dateSelector = &DateSelector::GetInstance();
    citySelector = new CitySelector();
    searchButton = new QPushButton("Search");

    QObject::connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search(bool)));

    QWidget *leftPanel = WidgetFactory::GetInstance ().produce_panel(dateSelector, citySelector, searchButton, 180);

    routeInfo = new ArrivalsTable();

    layout->addWidget(leftPanel);
    layout->addWidget(routeInfo);

    setLayout(layout);
}

void ArrivalsTab::search(bool checked) {
    if (!checked) {
        std::string station = citySelector->text().toStdString();
        Calendar date = dateSelector->getSelectedCalendar();
        std::string country = "Romania";

        json request;
        request["action"] = "arrivals";
        request["station"] = station;
        request["country"] = country;
        request["time"] = date.toJSON();
        auto future = std::async(std::launch::async, [request](){return Client::GetInstance().search(request);});

        auto timeout = future.wait_for (std::chrono::seconds (6));
        if (timeout == std::future_status::timeout) {
            Logger::GetInstance() << "Timeout reached\n";
            return;
        }
        emit routeInfo->feed(future.get());
    }
}