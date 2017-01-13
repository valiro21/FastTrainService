//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_DATESELECTOR_HPP
#define FASTTRAINSERVICE_DATESELECTOR_HPP


#include <QtWidgets/QVBoxLayout>
#include <QComboBox>
#include <JThread.hpp>
#include "Calendar.hpp"
#include "HourWidget.hpp"
#include "DateWidget.hpp"

class DateSelector : public QWidget {
private:
    DateSelector (QWidget *parent = 0);
    static DateSelector *instance;
    DateWidget *dateBox;
    HourWidget *hoursBox;
    JThread* update_thread;

public:
    std::vector<Calendar> days;
    static DateSelector& GetInstance (QWidget *parent = 0);
    Calendar& getSelectedCalendar ();
    void updateDate ();
};


#endif //FASTTRAINSERVICE_DATESELECTOR_HPP
