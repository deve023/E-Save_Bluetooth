/*! @file date_and_time.cpp Implementation of the relay date and time module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"

#include "date_and_time.h"

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
    startTime.tm_hour = 8;
    startTime.tm_min  = 0;
    startTime.tm_sec  = 0;

    endTime.tm_hour = 16;
    endTime.tm_min  = 0;
    endTime.tm_sec  = 0;

    printf("%s\n", "Functional time period set.");
}

bool isFunctionalTime()
{
    return true;
}

//=====[Implementations of private functions]==================================

