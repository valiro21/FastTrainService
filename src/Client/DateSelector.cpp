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
    hoursBox = new HourWidget();
    dateBox = new DateWidget();
    dateBox->setHoursBox(hoursBox);
    hoursBox->updateDate(true);
    updateDate();
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(dateBox);
    layout->addWidget(new QLabel("Search for trains after hour:"));
    layout->addWidget(hoursBox);
    setLayout(layout);

    unsigned int remaining_time =  (60 - Calendar().get(Calendar::MINUTE)) * 60 * 1000  + (60 - Calendar().get(Calendar::SECOND)) * 1000;

    // hourly update
    update_thread = new ScheduleThread ([this](){this->updateDate();}, remaining_time, 60*60*1000);
    update_thread->start ();
}

DateSelector* DateSelector::instance = 0;

DateSelector& DateSelector::GetInstance (QWidget *parent) {
    if (instance == 0) {
        instance = new DateSelector(parent);
    }
    return *instance;
}

Calendar& DateSelector::getSelectedCalendar () {
    Calendar *result = new Calendar();

    *result = days[dateBox->currentIndex()];

    std::string selected_hour = hoursBox->currentText().toStdString();
    if (selected_hour.size () == 0) {
        return *new Calendar();
    }
    else if (!('0'<= selected_hour[0] && selected_hour[0] <= '9') ) {
        return *new Calendar ();
    }
    else {
        int hour = std::stoi(selected_hour);
        result->set(hour, Calendar::HOUR);
        result->set(0, Calendar::MINUTE);
        result->set(0, Calendar::SECOND);
    }
    return *result;
}

void DateSelector::updateDate () {
    Calendar c;
    QStringList dates = QStringList();
    days.clear ();
    for (int i = 0; i < 7; i++) {
        dates << c.to_string().c_str();
        days.emplace_back (c);
        c.add(1, Calendar::DAY);
    }

    QStringListModel *dateModel = new QStringListModel();
    dateModel->setStringList(dates);
    int currentIndex = dateBox->currentIndex();
    dateBox->setModel(dateModel);
    if (currentIndex > 0) currentIndex--;
    else currentIndex = 0;
    dateBox->setCurrentIndex(currentIndex);
}