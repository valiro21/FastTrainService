//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_ROUTESTABLE_HPP
#define FASTTRAINSERVICE_ROUTESTABLE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <json/json.hpp>

using json = nlohmann::json;

class RoutesTable : public QTableWidget {
    Q_OBJECT
public:
    RoutesTable(QWidget *parent = Q_NULLPTR) : QTableWidget(parent) {}

    void setErrorHeader () {
        setColumnCount(1);
        QStringList header;
        header << "Error!";
        setColumnWidth(0, this->width());
        setRowCount(1);
        setHorizontalHeaderLabels(header);
    }

    void setDefaultHeader () {
        setColumnCount(1);
        setColumnWidth(0, this->width());
        QStringList header;
        header << "Press the search button to fetch results";
        setRowCount(0);
        setHorizontalHeaderLabels(header);
    }
public slots:
   virtual void feed (json response) = 0;
};

#endif //FASTTRAINSERVICE_ROUTESTABLE_HPP
