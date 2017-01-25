//
// Created by vrosca on 1/19/17.
//

#ifndef FASTTRAINSERVICE_INFORMATIONPANEL_HPP
#define FASTTRAINSERVICE_INFORMATIONPANEL_HPP


#include <Client/Tables/RoutesTable.hpp>
#include "Tables/ArrivalsTable.hpp"

class InformationPanel : public QWidget {
    static InformationPanel* instance;
    RoutesTable *table;
    InformationPanel(QWidget *parent = 0) : QWidget(parent) {}
public:
    static InformationPanel& GetInstance (QWidget *parent = 0);
    void feed (int type, json data);
};


#endif //FASTTRAINSERVICE_INFORMATIONPANEL_HPP
