//
// Created by vrosca on 1/25/17.
//

#include <QtGui/QWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <Client/src/Client.hpp>
#include <Utils/include/Logger.hpp>
#include "ArrivalsTable.hpp"

ArrivalsTable::ArrivalsTable(QWidget *parent) : RoutesTable(parent){
    setDefaultHeader ();
    for (int i = 0; i < ArrivalsTable::max_update_widgets; i++) {
        UpdateWidget *w = new UpdateWidget ();
        buttons.push_back (w);
    }
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(4000);
}

void ArrivalsTable::setHeader () {
    QStringList header;
    setColumnCount(5);
    setColumnWidth(0, 150);
    setColumnWidth(1, 150);
    setColumnWidth(2, 50);
    setColumnWidth(3, 180);
    setColumnWidth(4, 200);
    header << "Origin" << "Scheduled arrival time" << "Delay" << "Estimated arrival time" << "Action";
    setHorizontalHeaderLabels(header);
}

void ArrivalsTable::feed (json data) {
    changing = true;
    trips.clear ();
    arrivals.clear ();
    if (data.find("ERROR") != data.end ()) {
        setErrorHeader ();
        setItem(0, 0, new QTableWidgetItem(data["ERROR"].get<std::string>().c_str ()));
        changing = false;
        return;
    }
    setHeader();
    std::vector<json> results = data["RESULT"].get<std::vector<json> > ();
    setRowCount((int) results.size());

    for (int i = 0; i < results.size (); i++) {
        std::string station = results[i]["origin"]["name"];
        int delay = results[i]["delay"];
        std::string trip_id = results[i]["trip_id"];
        unsigned int arrival_time = results[i]["arrival"];
        Calendar c;
        c.setDayTimeUnix (arrival_time);
        arrivals.push_back(c);
        std::string arrival_time_str = c.getDayTimeStr ();

        c.add(delay, Calendar::MINUTE);

        std::string estimated = c.getDayTimeStr ();

        setItem(i, 0, new QTableWidgetItem(station.c_str()));
        setItem(i, 1, new QTableWidgetItem(arrival_time_str.c_str()));
        setItem(i, 2, new QTableWidgetItem(std::to_string(delay).c_str()));
        setItem(i, 3, new QTableWidgetItem(estimated.c_str()));
        setCellWidget(i, 4, buttons[i]);
        trips.push_back(trip_id);
        buttons[i]->setTripId(trip_id);
    }
    changing = false;
}

void ArrivalsTable::refresh () {
    json request;
    if (trips.size () == 0 || changing) {
        return;
    }

    request["trips"] = trips;
    json updatedTrips = Client::GetInstance().updateDelay (request);

    Logger::GetInstance().logd(updatedTrips.dump());
    std::vector<json> x = updatedTrips["RESULT"].get<std::vector<json> > ();
    for (int i = 0; i < x.size (); i++) {
        std::string trip_id = x[i]["trip_id"];
        int delay = x[i]["delay"];

        if (trip_id != trips[i]) return;

        Calendar estimated = arrivals[i];
        estimated.add(delay, Calendar::MINUTE);

        QTableWidgetItem *r2 = item(i, 2);
        r2->setText(std::to_string(delay).c_str());
        QTableWidgetItem *r3 = item(i, 3);
        r3->setText(estimated.to_complete_string().c_str());
    }
}