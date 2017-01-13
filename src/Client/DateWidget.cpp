//
// Created by vrosca on 1/13/17.
//

#include "DateWidget.hpp"

DateWidget::DateWidget(QWidget *parent) : QComboBox (parent) {
    QObject::connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexHasChanged(int)));
}

void DateWidget::setHoursBox (HourWidget *hourBox) {
    this->hoursBox = hourBox;
}

void DateWidget::currentIndexHasChanged(int index) {
    if (index == 0) {
        hoursBox->updateDate (true);
    }
    else {
        hoursBox->updateDate();
    }
}