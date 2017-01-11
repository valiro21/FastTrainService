//
// Created by vrosca on 1/10/17.
//

#include <ctime>
#include "Calendar.hpp"

Calendar::Calendar() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    year = (unsigned int) (now->tm_year + 1900);
    month = (unsigned int) now->tm_mon;
    day = (unsigned int) (now->tm_mday - 1);
    hour = (unsigned int) now->tm_hour;
    minute = (unsigned int) now->tm_min;
    second = (unsigned int) now->tm_sec;

}

int Calendar::get_days_of_month (int month) {
    if (month == 1 && isLeapYear ()) {
        return 29;
    }
    return days_in_month[month];
}

void Calendar::add (int val, int type) {
    int tmp_val;
    switch (type) {
        case SECOND:
            tmp_val = this->second + val;
            this->second = (unsigned int) (tmp_val % 60);
            this->add(tmp_val / 60, MINUTE);
            break;
        case MINUTE:
            tmp_val = this->minute + val;
            this->minute = (unsigned int) (tmp_val % 60);
            this->add(tmp_val / 60, HOUR);
            break;
        case HOUR:
            tmp_val = this->hour + val;
            this->hour = (unsigned int) (tmp_val % 24);
            this->add(tmp_val / 24, DAY);
            break;
        case DAY:
            tmp_val = this->day + val;
            while (tmp_val > get_days_of_month(this->month)) {
                tmp_val -= get_days_of_month(this->month);
                month++;
                month %= 12;
            }
            this->day = tmp_val;
            break;
        default:
            return;
    }
}

unsigned int Calendar::get (int type) {
    switch (type) {
        case SECOND:
            return second;
        case MINUTE:
            return minute;
        case HOUR:
            return hour;
        case DAY:
            return day + 1;
        case MONTH:
            return month + 1;
        case YEAR:
            return year;
        default:
            return 0;
    }
}

bool Calendar::isLeapYear () {
    if (year % 4) return false;
    else if (year % 100) return true;
    else return year % 400 == 0;
}

std::string Calendar::to_string() {
    return std::to_string(get(DAY)) + "-"+ std::to_string(get(MONTH)) + "-" + std::to_string(get(YEAR));
}