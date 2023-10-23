#include <string>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
std::string findMonth(int month)
{
    if (month == 1)
        return "January";
    else if (month == 2)
        return "Febuary";
    else if (month == 3)
        return "March";
    else if (month == 4)
        return "April";
    else if (month == 5)
        return "May";
    else if (month == 6)
        return "June";
    else if (month == 7)
        return "July";
    else if (month == 8)
        return "August";
    else if (month == 9)
        return "September";
    else if (month == 10)
        return "October";
    else if (month == 11)
        return "November";
    else if (month == 12)
        return "December";

    return "Fail";
}

std::string tableName(Date _todayDate, std::string group)
{
    std::string query = findMonth(_todayDate.tmonth) + std::to_string(_todayDate.tyear) + group;
    return query;
}

std::string toString(float number)
{
    std::string str = std::to_string(number);

    // Find the position of the decimal point
    size_t decimalPos = str.find('.');

    // If the decimal point is found, keep only one decimal place
    if (decimalPos != std::string::npos)
    {
        str = str.substr(0, decimalPos + 2); // Include one decimal place and the decimal point
    }

    return str;
}