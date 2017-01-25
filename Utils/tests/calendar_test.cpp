//
// Created by vrosca on 1/24/17.
//

#include <gtest/gtest.h>
#include <Calendar.hpp>
#include <sys/time.h>

TEST(CalendarTest, CalendarMinuteChange) {
    Calendar c;
    c.set(22, Calendar::HOUR);
    c.set(58, Calendar::MINUTE);
    c.set(59, Calendar::SECOND);
    c.add(1, Calendar::SECOND);
    ASSERT_EQ(c.get(Calendar::SECOND), 0);
}

TEST(CalendarTest, CalendarTotalChange) {
    Calendar c;
    c.set(1999,Calendar::YEAR);
    c.set(12, Calendar::MONTH);
    c.set(31, Calendar::DAY);
    c.set(23, Calendar::HOUR);
    c.set(59, Calendar::MINUTE);
    c.set(59, Calendar::SECOND);

    c.add(1, Calendar::SECOND);

    Calendar result(2000, 1, 1, 0, 0, 0);
    ASSERT_EQ(c.toUnixTime (), result.toUnixTime ());
}

TEST(CalendarTest, CalendarTotalChangeSubstract) {
    Calendar c(2000, 1, 1, 0, 0, 0);;
    c.add(-1, Calendar::SECOND);

    Calendar result(1999, 12, 31, 23, 59, 59);
    ASSERT_EQ(c.toUnixTime (), result.toUnixTime ());
}

TEST(CalendarTEst, RandomTime1) {
    Calendar c(1971, 2, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 34214400);
}

TEST(CalendarTest, RandomTime2) {
    Calendar c(1974, 1, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 126230400);
}

TEST(CalendarTest, RandomTime3) {
    Calendar c(1974, 6, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 139276800);
}

TEST(CalendarTest, RandomTime4) {
    Calendar c(1974, 12, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 155088000);
}

TEST(CalendarTest, RandomTime5) {
    Calendar c(1974, 11, 30, 23, 59, 59);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 155087999);
}

TEST(CalendarTest, RandomTime6) {
    Calendar c(1990, 1, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 631152000);
}

TEST(CalendarTest, RandomTime7) {
    Calendar c(2000, 1, 1, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 946684800);
}

TEST(CalendarTest, RandomTime8) {
    Calendar c(2000, 12, 31, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 978220800);
}

TEST(CalendarTest, RandomTime9) {
    Calendar c(2017, 12, 31, 0, 0, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 1514678400);
}

TEST(CalendarTest, RandomTime10) {
    Calendar c(2017, 1, 24, 20, 50, 0);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 1485291000);
}

TEST(CalendarTest, RandomTime11) {
    Calendar c(2017, 1, 24, 20, 50, 7);
    long long ct = c.toUnixTime ();
    ASSERT_EQ(ct / 1000LL, 1485291007);
}

TEST(CalendarTest, TestDay1) {
    Calendar c(2017, 1, 29, 20, 50, 7);
    ASSERT_EQ(c.getDayOfWeek(), 7);
}

TEST(CalendarTest, TestDay2) {
    Calendar c(2017, 2, 1, 20, 50, 7);
    ASSERT_EQ(c.getDayOfWeek(), 3);
}

TEST(CalendarTest, TestDay3) {
    Calendar c(2017, 1, 24, 20, 50, 7);
    ASSERT_EQ(c.getDayOfWeek(), 2);
}

TEST(CalendarTest, TestDay4) {
    Calendar c(2016, 3, 1, 0, 0, 0);
    ASSERT_EQ(c.getDayOfWeek(), 2);
}

TEST(CalendarTest, TestDayName1) {
    Calendar c(2017, 1, 22, 20, 50, 7);
    ASSERT_STREQ(c.getDayName().c_str(), "sunday");
}

TEST(CalendarTest, StringDay) {
    Calendar c(2017, 1, 22, 20, 50, 7);
    ASSERT_STREQ(c.getDayTimeStr().c_str(), "20:50:07");
}