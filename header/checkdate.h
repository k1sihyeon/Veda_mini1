#ifndef CHECKDATE_H
#define CHECKDATE_H

#include <regex>
using namespace std;

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day)
{
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

bool isValidDateFormat(const string& date)
{
    regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
    
    if (regex_match(date, datePattern)) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        return isValidDate(year, month, day);
    }
    return false;
}


#endif // CHECKDATE_H