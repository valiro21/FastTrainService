//
// Created by vrosca on 1/26/17.
//

#include "PathsTable.hpp"
#include <Calendar.hpp>

PathsTable::PathsTable(QWidget *parent) : RoutesTable(parent){
    setDefaultHeader ();
}

void PathsTable::setHeader () {
    QStringList header;
    setColumnCount(5);
    setColumnWidth(0, 120);
    setColumnWidth(1, 120);
    setColumnWidth(2, 140);
    setColumnWidth(3, 140);
    setColumnWidth(4, 400);
    header << "Start" << "End" << "Departure time" << "Arrival time" << "Route name";
    setHorizontalHeaderLabels(header);
}

void PathsTable::feed (json data) {
    if (data.find ("WAIT") != data.end ()) {
        setWaitingHeader ();
        return;
    }

    if (data.find("ERROR") != data.end ()) {
        setErrorHeader ();
        std::string msg = data["ERROR"].get<std::string>();
        setItem(0, 0, new QTableWidgetItem(msg.c_str ()));
        return;
    }

    setHeader();
    std::vector<json> results = data["RESULT"].get<std::vector<json> > ();
    setRowCount((int) results.size());
    Calendar time = Calendar::fromJSON(data["initial_calendar"]);

    for (int i = 0; i < results.size (); i++) {
        std::string station1 = results[i]["start"]["name"];
        std::string station2 = results[i]["end"]["name"];
        std::string route = results[i]["route"]["ShortName"];
        unsigned int duration = results[i]["duration"];
        unsigned int arrival_time = results[i]["arrival"];
        Calendar c2 = time;
        c2.add(arrival_time, Calendar::SECOND);
        Calendar c1 = c2;
        c1.add(-duration, Calendar::SECOND);

        std::string departure_time_str = c1.to_complete_string ();
        std::string arrival_time_str = c2.to_complete_string ();

        setItem(i, 0, new QTableWidgetItem(station1.c_str()));
        setItem(i, 1, new QTableWidgetItem(station2.c_str()));
        setItem(i, 2, new QTableWidgetItem(departure_time_str.c_str()));
        setItem(i, 3, new QTableWidgetItem(arrival_time_str.c_str()));
        setItem(i, 4, new QTableWidgetItem(route.c_str()));
    }
}