//
// Created by vrosca on 1/13/17.
//

#ifndef FASTTRAINSERVICE_DATEWIDGET_HPP
#define FASTTRAINSERVICE_DATEWIDGET_HPP


#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include "HourWidget.hpp"

class DateWidget : public QComboBox {
Q_OBJECT
private:
    HourWidget *hoursBox;
public:
    DateWidget(QWidget *parent = 0);
    void setHoursBox (HourWidget *hourBox);
private slots:
    void currentIndexHasChanged(int index);
};


#endif //FASTTRAINSERVICE_DATEWIDGET_HPP
