//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_CALENDAR_HPP
#define FASTTRAINSERVICE_CALENDAR_HPP


#include <string>

class Calendar {
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;

    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int get_days_of_month (int month);

public:
    enum {
        SECOND,
        MINUTE,
        HOUR,
        DAY,
        MONTH,
        YEAR
    };

    Calendar();
    void add (int val, int type);

    bool isLeapYear ();

    unsigned int get (int type);
    void set (int val, int type);

    std::string to_string ();
};


#endif //FASTTRAINSERVICE_CALENDAR_HPP
