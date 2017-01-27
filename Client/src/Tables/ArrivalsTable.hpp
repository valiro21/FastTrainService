//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_ARRIVALSTABLE_HPP
#define FASTTRAINSERVICE_ARRIVALSTABLE_HPP

#include "Client/src/UpdateWidget.hpp"
#include "RoutesTable.hpp"
#include <QTimer>
#include <Calendar.hpp>
#include <mutex>

class ArrivalsTable : public RoutesTable {
Q_OBJECT
    static const int max_update_widgets = 200;
public:
    ArrivalsTable(QWidget *parent = 0);
    void setHeader ();
    std::vector<std::string> trips;
    std::vector<UpdateWidget*> buttons;
    std::vector<Calendar> arrivals;
    void feed (json data);
    bool changing;
    QTimer *timer;

public slots:
    void refresh();
};


#endif //FASTTRAINSERVICE_ARRIVALSTABLE_HPP
