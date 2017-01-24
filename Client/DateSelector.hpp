//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_DATESELECTOR_HPP
#define FASTTRAINSERVICE_DATESELECTOR_HPP


#include <QtWidgets/QVBoxLayout>
#include <QComboBox>
#include <JThread.hpp>
#include <Calendar.hpp>
#include <QtWidgets/QDateTimeEdit>

class DateSelector : public QWidget {
private:
    DateSelector (QWidget *parent = 0);
    static DateSelector *instance;
    QDateTimeEdit *qDateTime;
public:
    static DateSelector& GetInstance (QWidget *parent = 0);
    Calendar getSelectedCalendar ();
};


#endif //FASTTRAINSERVICE_DATESELECTOR_HPP
