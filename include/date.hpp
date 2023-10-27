#pragma once
#include <cstring>
#include <ctime>
#include "leap.h"
#include <iostream>
#include <string>

class Date
{
public:
    int tyear, tmonth, tday;

    /// @brief
    Date();
    Date(std::string date);
};

class Age
{
public:
    int years, months, days;

public:
    Age(Date _todayDate, Date date);
};

Date::Date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    tyear = 1900 + ltm->tm_year; // today's year
    tmonth = 1 + ltm->tm_mon;    // todays Month
    tday = ltm->tm_mday;
}

Age::Age(Date _birthDate, Date date)
{
    int MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    years = date.tyear;
    months = date.tmonth;
    days = date.tday;
    // birth's day
    if (leap::is_leap_year(years)) // for leap year case
        MONTH[1] = 29;

    years = years - _birthDate.tyear; // age year

    months > _birthDate.tmonth ? months = months - _birthDate.tmonth : (--years, months = 12 - _birthDate.tmonth + months); // age month

    days > _birthDate.tday ? days = days - _birthDate.tday : (--months, days = (MONTH[_birthDate.tmonth - 1] - _birthDate.tday + days)); // age day

    if (days == MONTH[_birthDate.tmonth])
    {
        days = 0;
        ++months;
    }

    if (months == 12)
    {
        months = 0;
        ++years;
    }
    // std::cout << "Age: Year=" << years << "\tMonths = " << months << "\tday = " << days << std::endl;
    //    return this;
}

Date::Date(std::string date_string)
{
    tm date = {0};
    strptime(date_string.c_str(), "%Y-%m-%d", &date);

    // Extract the year, month, and day
    tyear = date.tm_year + 1900;
    tmonth = date.tm_mon + 1;
    tday = date.tm_mday;
}