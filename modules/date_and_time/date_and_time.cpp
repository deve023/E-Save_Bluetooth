/*! @file date_and_time.cpp Implementation of the date and time module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"
#include "time.h"

#include "date_and_time.h"

//=====[Declaration and initialization of private global variables]============

static struct tm startTime;    ///> Start time for the functional time.
static struct tm endTime;      ///> End time for the functional time.

//=====[Implementations of public functions]===================================

char* dateAndTimeRead()
{
    time_t current_time;
    current_time = time(NULL);
    return ctime(&current_time);
}

void functionalTimeRead(int *v)
{
    v[0] = startTime.tm_hour;
    v[1] = startTime.tm_min;
    v[2] = startTime.tm_sec;
    v[3] = endTime.tm_hour;
    v[4] = endTime.tm_min;
    v[5] = endTime.tm_sec;
}

void dateAndTimeWrite( int year, int month, int day, int hour, int minute, int second )
{
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;
    rtcTime.tm_mon  = month - 1;
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) );
}

void setFunctionalTimePeriod(int sHour, int sMin, int sSec, int eHour, int eMin, int eSec)
{
    startTime.tm_hour = sHour;
    startTime.tm_min  = sMin;
    startTime.tm_sec  = sSec;

    endTime.tm_hour = eHour;
    endTime.tm_min  = eMin;
    endTime.tm_sec  = eSec;
}

bool isFunctionalTime()
{
    bool isAfterStartTime = false;
    bool isBeforeEndTime = false;

    time_t current_time = time(NULL);
    struct tm * now = localtime(&current_time);

    if(now->tm_hour > startTime.tm_hour) {
        isAfterStartTime = true;
    } else if(now->tm_hour == startTime.tm_hour)  {
        if(now->tm_min > startTime.tm_min) {
            isAfterStartTime = true;
        } else if(now->tm_min == startTime.tm_min) {
            if(now->tm_sec > startTime.tm_sec) {
                isAfterStartTime = true;
            }
        }
    }

    if(now->tm_hour < endTime.tm_hour) {
        isBeforeEndTime = true;
    } else if(now->tm_hour == endTime.tm_hour)  {
        if(now->tm_min < endTime.tm_min) {
            isBeforeEndTime = true;
        } else if(now->tm_min == endTime.tm_min) {
            if(now->tm_sec < endTime.tm_sec) {
                isBeforeEndTime = true;
            }
        }
    }

    return isAfterStartTime && isBeforeEndTime;
}

//=====[Implementations of private functions]==================================
