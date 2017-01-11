//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_ACTIONSELECTOR_HPP
#define FASTTRAINSERVICE_ACTIONSELECTOR_HPP


#include <QtWidgets/QTabWidget>

class ActionSelector : public QTabWidget {
public:
    ActionSelector(QWidget *parent = 0);
};

extern QVBoxLayout* createCityLayout ();


#endif //FASTTRAINSERVICE_ACTIONSELECTOR_HPP
