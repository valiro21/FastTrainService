//
// Created by vrosca on 1/25/17.
//

#include <Calendar.hpp>
#include "ArrivalsTable.hpp"

ArrivalsTable::ArrivalsTable(QWidget *parent) : RoutesTable(parent){
    QStringList header;
    header << "Origin" << "Scheduled arrival time" << "Delay" << "Estimated arrival time" << "Action";
    setHorizontalHeaderLabels(header);
}

void ArrivalsTable::feed (json data) {
    std::vector<json> results = data["RESULT"].get<std::vector<json> > ();
    setColumnCount(results.size());

    for (int i = 0; i < results.size (); i++) {
        std::string station = results[i]["origin"]["name"];
        int delay = results[i]["delay"];
        unsigned int arrival_time = results[i]["arrival"];
        Calendar c;
        c.setDayTimeUnix (arrival_time);

        std::string arrival_time_str = c.getDayTimeStr ();

        c.add(delay, Calendar::SECOND);

        std::string estimated = c.getDayTimeStr ();

        setItem(i, 0, new QTableWidgetItem(station.c_str()));
        setItem(i, 1, new QTableWidgetItem(arrival_time_str.c_str()));
        setItem(i, 2, new QTableWidgetItem(std::to_string(delay).c_str()));
        setItem(i, 3, new QTableWidgetItem(estimated.c_str()));
    }

}