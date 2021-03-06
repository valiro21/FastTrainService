//
// Created by vrosca on 1/10/17.
//

#include <ctime>
#include "Calendar.hpp"

int Calendar::days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Calendar::Calendar() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    year = (unsigned int) (now->tm_year + 1900);
    month = (unsigned int) now->tm_mon + 1;
    day = (unsigned int) (now->tm_mday);
    hour = (unsigned int) now->tm_hour;
    minute = (unsigned int) now->tm_min;
    second = (unsigned int) now->tm_sec;
}

int Calendar::get_days_of_month (int month) {
    if (month == 2 && isLeapYear ()) {
        return 29;
    }
    return days_in_month[month];
}

void Calendar::add (int val, int type) {
    int tmp_val, reminder = 0;
    switch (type) {
        case SECOND:
            tmp_val = second + val;
            if (tmp_val < 0) {
                second = (unsigned int)  (60 + tmp_val % 60);
                if (second == 60) {
                    reminder = 1;
                    second = 0;
                }
                reminder += -1 + tmp_val / 60;
            }
            else {
                second = (unsigned int) (tmp_val % 60);
                reminder = tmp_val / 60;
            }

            add(reminder, MINUTE);
            break;
        case MINUTE:
            tmp_val = minute + val;
            if (tmp_val < 0) {
                minute = (unsigned int)  (60 + tmp_val % 60);
                if (minute == 60) {
                    reminder = 1;
                    minute = 0;
                }
                reminder = -1 + tmp_val / 60;
            }
            else {
                minute = (unsigned int) (tmp_val % 60);
                reminder = tmp_val / 60;
            }

            add(reminder, HOUR);
            break;
        case HOUR:
            tmp_val = hour + val;
            if (tmp_val < 0) {
                hour = (unsigned int)  (24 + tmp_val % 24);
                if (hour == 24) {
                    reminder = 1;
                    hour = 0;
                }
                reminder = -1 + tmp_val / 24;
            }
            else {
                hour = (unsigned int) (tmp_val % 24);
                reminder = tmp_val / 24;
            }
            add(reminder, DAY);
            break;
        case DAY:
            tmp_val = day + val;
            while (tmp_val > get_days_of_month(this->month)) {
                tmp_val -= get_days_of_month(this->month);
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
            }

            while (tmp_val < 1) {
                unsigned int m = month - 1;
                if (m == 0) {
                    m = 12;
                    year--;
                }

                tmp_val += get_days_of_month(m);
                month = m;
            }

            day = (unsigned int) tmp_val;
            break;
        default:
            return;
    }
}

void Calendar::set (int val, int type) {
    switch (type) {
        case SECOND:
            if (0 <= val && val < 60) {
                second = (unsigned int) val;
            }
            break;
        case MINUTE:
            if (0 <= val && val < 60) {
                minute = (unsigned int) val;
            }
            break;
        case HOUR:
            if (0 <= val && val < 24) {
                hour = (unsigned int) val;
            }
            break;
        case DAY:
            if (1 <= val && val <= get_days_of_month(month))
                day = (unsigned int) val;
            break;
        case MONTH:
            if (1 <= val && val <= 12)
                month = (unsigned int) val;
            break;
        case YEAR:
            year = (unsigned int) val;
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
            return day;
        case MONTH:
            return month;
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

bool Calendar::isLeapYear (int year) {
    if (year % 4) return false;
    else if (year % 100) return true;
    else return year % 400 == 0;
}

std::string Calendar::to_string() {
    return std::to_string(get(DAY)) + "/"+ std::to_string(get(MONTH)) + "/" + std::to_string(get(YEAR));
}

json Calendar::toJSON () {
    json calendar;

    calendar["year"] = get(YEAR);
    calendar["month"] = get(MONTH);
    calendar["day"] = get(DAY);
    calendar["hour"] = get(HOUR);
    calendar["minute"] = get(MINUTE);
    calendar["second"] = get(SECOND);

    return calendar;
}

Calendar Calendar::fromJSON (json json_calendar) {
    Calendar calendar;

    calendar.set(json_calendar["year"].get<int>(), Calendar::YEAR);
    calendar.set(json_calendar["month"].get<int>(), Calendar::MONTH);
    calendar.set(json_calendar["day"].get<int>(), Calendar::DAY);
    calendar.set(json_calendar["hour"].get<int>(), Calendar::HOUR);
    calendar.set(json_calendar["minute"].get<int>(), Calendar::MINUTE);
    calendar.set(json_calendar["second"].get<int>(), Calendar::SECOND);

    return calendar;
}

int Calendar::getDayOfWeek () const {
    int k = day;
    int m = month - 2;
    if (m < 1) m = 12 + m;
    int C = year / 100;
    int Y = year % 100;
    if (month <= 2) Y--;

    int reminder = (k + int (2.6 * (double)m - 0.2) - 2 * C + Y + int ((double)Y / 4.0) + int ((double)C / 4.0));
    if (reminder < 0) {
        reminder = 7 + (reminder % 7);
    }
    else{
        reminder = reminder % 7;
    }
    if (reminder == 0) reminder = 7;
    return reminder;
}

std::string Calendar::getDayName () {
    int dayOfWeek = getDayOfWeek ();

    switch (dayOfWeek) {
        case 1: return "monday";
        case 2: return "tuesday";
        case 3: return "wednesday";
        case 4: return "thursday";
        case 5: return "friday";
        case 6: return "saturday";
        case 7: return "sunday";
        default: return "date not found";
    }
}

Calendar::Calendar(int year, int month, int day, int hour, int minute, int second) {
    set(year, Calendar::YEAR);
    set(month, Calendar::MONTH);
    set(day, Calendar::DAY);
    set(hour, Calendar::HOUR);
    set(minute, Calendar::MINUTE);
    set(second, Calendar::SECOND);
}

long long Calendar::toUnixTime () {
    long long time = 0;

    time += get(Calendar::SECOND);
    time += get(Calendar::MINUTE) * 60;
    time += get(Calendar::HOUR) * 60LL * 60LL;
    time += ((long long)get(Calendar::DAY) - 1) * 24LL * 60LL * 60LL;
    int m = get(Calendar::MONTH);
    while (m > 1) {
        time += (long long)(get_days_of_month(m-1)) * 24LL * 60LL * 60LL;
        m--;
    }

    int y = get(Calendar::YEAR);
    while (y > 1970) {
        long long d = 365;
        if (Calendar::isLeapYear(y-1))
            d++;

        time += d * 24 * 60 * 60;
        y--;
    }
    return time * 1000;
}

void Calendar::setDayTimeUnix (unsigned long long time) {
    int h = time / 3600; time -= h * 3600;
    int m = time / 60;
    int s = time % 60;

    set (s, Calendar::SECOND);
    set (m, Calendar::MINUTE);
    set (h, Calendar::HOUR);
}

unsigned long long Calendar::getDayTimeUnix () {
    return get(Calendar::HOUR) * 60 * 60 + get(Calendar::MINUTE) * 60 + get(Calendar::SECOND);
}

std::string Calendar::getDayTimeStr () {
    std::string h = Calendar::toZeroStr (get(Calendar::HOUR));
    std::string m = Calendar::toZeroStr (get(Calendar::MINUTE));
    std::string s = Calendar::toZeroStr (get(Calendar::SECOND));
    return h + ':' + m + ':' + s;
}

std::string Calendar::toZeroStr (int val) {
    std::string s;
    if (val < 10) {
        s = "0";
    }
    s += std::to_string(val);
    return s;
}

std::string Calendar::to_complete_string () {
    std::string s = to_string ();
    s += " ";
    s += getDayTimeStr();
    return s;
}