/*! @file date_and_time.cpp Implementation of the relay date and time module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"

#include "date_and_time.h"

#include "time.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

static struct tm startTime;    ///> Time to activate sensor and control logic.
static struct tm endTime;      ///> Time to deactivate sensor and control logic.

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

char* dateAndTimeRead()
{
    time_t epochSeconds;
    epochSeconds = time(NULL);
    return ctime(&epochSeconds);    // Starts the internal RTC.
}

void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second )
{
    struct tm rtcTime;

    rtcTime.tm_year = year - 1900;
    rtcTime.tm_mon  = month - 1;
    rtcTime.tm_mday = day;
    rtcTime.tm_hour = hour;
    rtcTime.tm_min  = minute;
    rtcTime.tm_sec  = second;

    rtcTime.tm_isdst = -1;

    set_time( mktime( &rtcTime ) ); // Sets internal RTC time.
}

void setFunctionalTimePeriod()
{
    startTime.tm_year = 10;
    startTime.tm_mon  = 0;
    startTime.tm_mday = 1;
    startTime.tm_hour = 8;
    startTime.tm_min  = 0;
    startTime.tm_sec  = 0;
    startTime.tm_isdst = -1;

    endTime.tm_year = 10;
    endTime.tm_mon  = 0;
    endTime.tm_mday = 1;
    endTime.tm_hour = 16;
    endTime.tm_min  = 0;
    endTime.tm_sec  = 0;
    endTime.tm_isdst = -1;

    printf("%s\n", "Functional time period set.");
}

bool isFunctionalTime()
{
    bool isFuncTime = false;
    time_t epochSeconds = time(NULL);
    struct tm * now = localtime(&epochSeconds);

    if(now->tm_hour > startTime.tm_hour & now->tm_hour < endTime.tm_hour) {
        isFuncTime = true;
    } else if(now->tm_min > startTime.tm_min & now->tm_min < endTime.tm_min) {
        isFuncTime = true;
    } else if(now->tm_sec > startTime.tm_sec & now->tm_sec < endTime.tm_sec) {
        isFuncTime = true;
    }

    return isFuncTime;
}

//=====[Implementations of private functions]==================================
