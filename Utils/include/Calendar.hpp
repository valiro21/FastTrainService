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
    static std::string toZeroStr (int val);
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

    /** Add unit to calendar.
     *  Add user defined number of units to calendar. Types of units:
     *  CALENDAR::SECOND
     *  CALENDAR::MINUTE
     *  CALENDAR::HOUR
     *  CALENDAR::DAY
     *  CALENDAR::MONTH
     *  CALENDAR::YEAR
     *  Units can also be negative
     * @param val number of units
     * @param type unit type
     */
    void add (int val, int type);

    bool isLeapYear (); ///Check if the given year is a leap year.

    /** Get field from calendar.
     *  Get field by type from the calendar. Types of units:
     *  CALENDAR::SECOND
     *  CALENDAR::MINUTE
     *  CALENDAR::HOUR
     *  CALENDAR::DAY
     *  CALENDAR::MONTH
     *  CALENDAR::YEAR
     * @param type unit type
     */
    unsigned int get (int type);


    /** Set unit to calendar.
     *  Set user defined number of units to calendar. Types of units:
     *  CALENDAR::SECOND
     *  CALENDAR::MINUTE
     *  CALENDAR::HOUR
     *  CALENDAR::DAY
     *  CALENDAR::MONTH
     *  CALENDAR::YEAR
     *  Units will not be set if not in the usual range. ex: for month the range is [1,12]
     * @param val number of units
     * @param type unit type
     */
    void set (int val, int type);

    /** Converts internal date to str.
     * Date will be in format
     * DD/MM/YYYY
     * @return a string representing the internal date
     */
    std::string to_string ();

    /** Converts internal date to json.
     * The respective fields will be:
     * "year"
     * "month"
     * "day"
     * "hour"
     * "minute"
     * "second"
     * @return a string representing the internal date
     */
    json toJSON ();

    /** Converts a json to a string.
     * The respective field the json should have are:
     * "year"
     * "month"
     * "day"
     * "hour"
     * "minute"
     * "second"
     * @param json_calendar A json representing the calendar
     * @return Calendar object
     */
    static Calendar fromJSON (json json_calendar);

    /** Day in week.
     * Returns a number representing the number of day in the week. The following mapping is used:
     * 1 - Monday
     * 2 - Thursday
     * 3 - Wednesday
     * 4 - Tuesday
     * 5 - Friday
     * 6 - Saturday
     * 7 - Sunday
     * @return integer representing the day number
     */
    int getDayOfWeek () const;

    /** Returns the day name.
     * Returns the day name in English.
     * The following dates can be returned:
     * monday
     * thursday
     * wednesday
     * tuesday
     * friday
     * saturday
     * sunday
     * @return string representing the day name
     */
    std::string getDayName ();

    /** Convert date and time to unix time.
     * Convers the internal date of the calendar to unix time (1970/1/1)
     * This representation includes milliseconds.
     * @return 64bit integer representing the unix time
     */
    long long toUnixTime ();

    static bool isLeapYear (int year); /// Check if the given year is a leap year.

    /** Sets the current day H
     * Only the hour, minutes and seconds are affected.
     * @param time
     */
    void setDayTimeUnix (unsigned long long time);

    /** Convert only time to unix time.
     * Convers the internal time of day to "unix" time (00:00:00)
     * This representation does not includes milliseconds.
     * @return 64bit integer representing the unix time
     */
    unsigned long long getDayTimeUnix ();

    /** Converts internal time to str.
     * Date will be in format
     * HH:MM:SS
     * @return a string representing the internal date
     */
    std::string getDayTimeStr ();

    /** Converts internal date and time to str.
     * Date will be in format
     * DD/MM/YYYY HH:MM:SS
     * @return a string representing the internal date
     */
    std::string to_complete_string ();
};

#endif //FASTTRAINSERVICE_CALENDAR_HPP
