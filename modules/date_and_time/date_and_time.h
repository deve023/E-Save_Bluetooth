/*! @file date_and_time.h Header file for the day and time module.
 *
 * @note This module serves to set the date and time of the system.
 */

//=====[#include guards - begin]===============================================

#ifndef _DATE_AND_TIME_H_
#define _DATE_AND_TIME_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Reads the current date and time.
 * 
 * @return String [char *] current date and time.
 */
char* dateAndTimeRead();

/**
 * @brief Sets a date and time.
 * 
 */
void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second );

//=====[#include guards - end]=================================================

#endif // _DATE_AND_TIME_H_