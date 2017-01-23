//
// Created by vrosca on 1/13/17.
//

#ifndef FASTTRAINSERVICE_TIMEWIDGET_HPP
#define FASTTRAINSERVICE_TIMEWIDGET_HPP


#include <QtWidgets/QComboBox>

class HourWidget : public QComboBox {
public:
    HourWidget(QWidget *parent = 0);
    void updateDate (bool current_day = 0);
};


#endif //FASTTRAINSERVICE_TIMEWIDGET_HPP
