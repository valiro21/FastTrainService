//
// Created by vrosca on 1/10/17.
//

#include <QtWidgets/QComboBox>
#include <QtCore/QStringListModel>
#include <QtWidgets/QLabel>
#include "DateSelector.hpp"
#include "Calendar.hpp"

DateSelector::DateSelector (QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();

    QComboBox *dateBox = new QComboBox();

    Calendar c;
    QStringList dates = QStringList();
    for (int i = 0; i < 7; i++) {
        dates << c.to_string().c_str();
        c.add(1, Calendar::DAY);
    }

    QStringListModel *dateModel = new QStringListModel();
    dateModel->setStringList(dates);
    dateBox->setModel(dateModel);

    QComboBox* hoursBox = new QComboBox();


    Calendar c2;
    QStringListModel *hourModel = new QStringListModel();
    QStringList hours = QStringList();


    hours << "CURRENT TIME";
    for (int i = c2.get(Calendar::HOUR) + 1; i <= 23; i++) {
        hours << std::to_string (i).c_str();
    }
    hourModel->setStringList(hours);
    hoursBox->setModel(hourModel);

    QLabel *dateLabel = new QLabel();
    dateLabel->setText("Date:");

    QLabel *hourLabel = new QLabel();
    hourLabel->setText("Trains after hour:");

    setFixedHeight(200);
    setFixedWidth(300);

    layout->addWidget(dateLabel);
    layout->addWidget(dateBox);
    layout->addWidget(hourLabel);
    layout->addWidget(hoursBox);

    setLayout(layout);
}