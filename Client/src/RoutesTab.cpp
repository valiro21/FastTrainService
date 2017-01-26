//
// Created by vrosca on 1/26/17.
//

#include "RoutesTab.hpp"
#include <QtWidgets/QHBoxLayout>
#include <Logger.hpp>
#include <QtWidgets/QLabel>
#include "Client.hpp"
#include "WidgetFactory.hpp"
#include "Tables/PathsTable.hpp"

RoutesTab::RoutesTab (QWidget *parent) : QWidget(parent) {
    QLayout *layout = new QHBoxLayout ();

    dateSelector = &DateSelector::GetInstance();
    citySelectorStart = new CitySelector();
    citySelectorEnd = new CitySelector();
    searchButton = new QPushButton("Search");
    searchButton->setFixedHeight(30);
    searchButton->setFixedWidth(160);

    QWidget *citySelectors = new QWidget();
    QLayout *cityLayout = new QVBoxLayout();
    cityLayout->addWidget(new QLabel ("Origin city"));
    cityLayout->addWidget(citySelectorStart);
    cityLayout->addWidget(new QLabel ("Destination city"));
    cityLayout->addWidget(citySelectorEnd);
    citySelectors->setLayout(cityLayout);

    QObject::connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search(bool)));

    QWidget *leftPanel = WidgetFactory::GetInstance ().produce_panel(dateSelector, citySelectors, searchButton, 280);

    routeInfo = new PathsTable();

    layout->addWidget(leftPanel);
    layout->addWidget(routeInfo);
    setLayout(layout);
}

void RoutesTab::search(bool checked) {
    if (!checked) {
        std::string start = citySelectorStart->text().toStdString();
        std::string end = citySelectorEnd->text().toStdString();
        Calendar date = dateSelector->getSelectedCalendar();
        std::string country = "Romania";

        json request;
        request["action"] = "path";
        request["origin"] = start;
        request["destination"] = end;
        request["time"] = date.toJSON();
        auto future = std::async(std::launch::async, [request](){return Client::GetInstance().search(request);});

        auto timeout = future.wait_for (std::chrono::seconds (12));
        if (timeout == std::future_status::timeout) {
            Logger::GetInstance() << "Timeout reached\n";
            return;
        }
        json result = future.get();
        result["initial_calendar"] = date.toJSON();
        emit routeInfo->feed(result);
    }
}