//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_CALENDAR_HPP
#define FASTTRAINSERVICE_CALENDAR_HPP


#include <string>
#include "json/json.hpp"

using json = nlohmann::json;

class Calendar {
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;

    int get_days_of_month (int month);
    static int days_in_month[13];
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
    Calendar(int year, int month, int day, int hour, int minute, int second);
    void add (int val, int type);

    bool isLeapYear ();

    unsigned int get (int type);
    void set (int val, int type);

    std::string to_string ();

    json toJSON ();

    int getDayOfWeek () const;
    std::string getDayName ();

    long long toUnixTime ();

    static bool isLeapYear (int year);
};

#endif //FASTTRAINSERVICE_CALENDAR_HPP
