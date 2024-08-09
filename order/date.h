#ifndef DATE_H
#define DATE_H

#include <ctime>  // time_t, tm, time, localtime

// Date 구조체
struct Date {
    int year;
    int month;
    int day;
    int hour;
};

Date getCurrentTime() {
    time_t t = time(0);  // 현재 시간을 가져옴
    tm* now = localtime(&t);  // 현재 시간을 tm 구조체로 변환

    Date currentTime;
    currentTime.year = now->tm_year + 1900;  // tm_year는 1900년부터 시작하므로, 1900을 더해야 함
    currentTime.month = now->tm_mon + 1;  // tm_mon은 0부터 시작하므로, 1을 더해야 함
    currentTime.day = now->tm_mday;
    currentTime.hour = now->tm_hour;

    return currentTime;
}
#endif // DATE_H

