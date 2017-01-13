//
// Created by vrosca on 1/13/17.
//

#include <QtWidgets/QVBoxLayout>
#include <QtCore/QStringListModel>
#include "HourWidget.hpp"
#include "Calendar.hpp"

HourWidget::HourWidget(QWidget *parent) : QComboBox(parent) {
}

void HourWidget::updateDate (bool current_day) {
    QStringListModel *hourModel = new QStringListModel();
    QStringList hours = QStringList();

    if (current_day) {
        Calendar c;
        hours << "CURRENT TIME";
        for (int i = c.get(Calendar::HOUR) + 1; i <= 23; i++) {
            hours << std::to_string(i).c_str();
        }
    }
    else {
        // add single digit hours
        for (int i = 0; i <= 9; i++) {
            hours << ("0" + std::to_string (i)).c_str();
        }
        for (int i = 10; i < 24; i++) {
            hours << (std::to_string (i)).c_str();
        }
    }
    hourModel->setStringList(hours);
    setModel(hourModel);
}