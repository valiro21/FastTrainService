//
// Created by vrosca on 1/25/17.
//

#include <Calendar.hpp>
#include "DeparturesTable.hpp"

DeparturesTable::DeparturesTable(QWidget *parent) : RoutesTable(parent){
    setDefaultHeader ();
}

void DeparturesTable::setHeader () {
    QStringList header;
    setColumnCount(3);
    setColumnWidth(0, 150);
    setColumnWidth(1, 150);
    setColumnWidth(2, 180);
    header << "Destination" << "Departure time" << "Arrival time at destination";
    setHorizontalHeaderLabels(header);
}

void DeparturesTable::feed (json data) {
    if (data.find("ERROR") != data.end ()) {
        setErrorHeader ();
        std::string msg = data["ERROR"].get<std::string>();
        setItem(0, 0, new QTableWidgetItem(msg.c_str ()));
        return;
    }

    setHeader();
    std::vector<json> results = data["RESULT"].get<std::vector<json> > ();
    setRowCount((int) results.size());

    for (int i = 0; i < results.size (); i++) {
        std::string station = results[i]["endpoint"]["name"];
        unsigned int departure_time = results[i]["departure"];
        unsigned int arrival_time = results[i]["arrival"];
        Calendar c1, c2;
        c1.setDayTimeUnix (departure_time);
        c2.setDayTimeUnix (arrival_time);

        std::string departure_time_str = c1.to_complete_string ();

        std::string arrival_time_str = c2.to_complete_string ();

        setItem(i, 0, new QTableWidgetItem(station.c_str()));
        setItem(i, 1, new QTableWidgetItem(departure_time_str.c_str()));
        setItem(i, 2, new QTableWidgetItem(arrival_time_str.c_str()));
    }
}