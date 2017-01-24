//
// Created by vrosca on 1/10/17.
//
#include <QtCore/QStringListModel>
#include <QtWidgets/QLabel>
#include <Utils.hpp>
#include <ScheduleThread.hpp>
#include "DateSelector.hpp"

DateSelector::DateSelector (QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Date:"));
    qDateTime = new QDateTimeEdit();
    qDateTime->setDate(QDate::currentDate());
    qDateTime->setTime(QTime::currentTime());
    qDateTime->setCalendarPopup(true);
    layout->addWidget(qDateTime);
    setLayout(layout);
}

DateSelector* DateSelector::instance = 0;

DateSelector& DateSelector::GetInstance (QWidget *parent) {
    if (instance == 0) {
        instance = new DateSelector(parent);
    }
    return *instance;
}

Calendar DateSelector::getSelectedCalendar () {
    QDate selectedDate = qDateTime->date();
    QTime selectedTime = qDateTime->time();

    int year, month, day;
    selectedDate.getDate(&year, &month, &day);
    int hour = selectedTime.hour();
    int minute = selectedTime.minute();
    int second = selectedTime.second();

    Calendar c;
    c.set(second, Calendar::SECOND);
    c.set(minute, Calendar::MINUTE);
    c.set(hour, Calendar::HOUR);
    c.set(day, Calendar::DAY);
    c.set(month, Calendar::MONTH);
    c.set(year, Calendar::YEAR);

    return c;
}