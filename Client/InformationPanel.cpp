//
// Created by vrosca on 1/19/17.
//

#include <QtWidgets/QScrollArea>
#include <QtGui/QtGui>
#include <QtWidgets/QVBoxLayout>
#include <future>
#include <Utils.hpp>
#include "InformationPanel.hpp"

InformationPanel* InformationPanel::instance = nullptr;

InformationPanel& InformationPanel::GetInstance (QWidget *parent) {
    if (instance == nullptr) {
        instance = new InformationPanel(parent);
    }
    return *instance;
}

void InformationPanel::feed (int type, json data) {
    if (table != NULL)
        delete table;

    if (type == 0) {
        table = new ArrivalsTable(this);
        table->feed(data);
    }
}