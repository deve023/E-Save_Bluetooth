/*! @file date_and_time.h Header file for the date and time module.
 *
 * @note This module serves to handle current date and time and functional time settings.
 */

//=====[#include guards - begin]===============================================

#ifndef _DATE_AND_TIME_H_
#define _DATE_AND_TIME_H_

//=====[Declaration of public defines]=========================================

#define DATE_AND_TIME_DEFAULT 2000, 1, 1, 0, 0, 0   ///> Default date and time:     (YYYY, MM, DD, hh, mm, ss)
#define FUNCTIONAL_TIME_DEFAULT 0, 0, 0, 0, 0, 0    ///> Default functional time:   (hh, mm, dd, hh, mm, dd)

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Reads the current date and time.
 * 
 * @return String [char *]: current date and time.
 */
char* dateAndTimeRead();

/**
 * @brief Reads the functional time period and saves the data
 * in vector v passed by argument:
 *
 * v[0]: start hour
 * v[1]: start minute
 * v[2]: start second
 * v[3]: finish hour
 * v[4]: finish minute
 * v[5]: finish second
 * 
 * v needs to have allocated memory for 6 int components.
 *
 */
void functionalTimeRead(int *v);

/**
 * @brief Sets a date and time.
 * 
 * @param[in] current_date_and_time YYYY, MM, DD, hh, mm, ss as integers.
 */
void dateAndTimeWrite(int year, int month, int day, int hour, int minute, int second);

/**
 * @brief Sets a time period in which the program is functional.
 * 
 * Prerequisite: start_time has to be earlier than end_time.
 *
 * @param[in] start_time hh, mm, ss as integers.
 * @param[in] end_time hh, mm, ss as integers.
 */
void setFunctionalTimePeriod(int sHour, int sMin, int sSec, int eHour, int eMon, int eSec);

/**
 * @brief Checks if the current time is within the functional period.
 * 
 * @return Boolean indicating if the current time is a functional time.
 */
bool isFunctionalTime();

//=====[#include guards - end]=================================================

#endif // _DATE_AND_TIME_H_