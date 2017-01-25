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
public:
    RoutesTable(QWidget *parent = Q_NULLPTR) : QTableWidget(parent) {}
    virtual void feed (json response) = 0;
};

#endif //FASTTRAINSERVICE_ROUTESTABLE_HPP
