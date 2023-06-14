/*! @file energy_save_system.cpp Implementation of the system module.
 *
 */

//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "energy_save_system.h"

#include "actuator.h"
#include "motion_sensor.h"
#include "relay_control.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

DigitalOut functionalTimeLed(LED2);  ///> Led to indicate functional time.

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void energySaveSystemInit()
{
    actuatorInit(SYSTEM_TIME_INCREMENT_MS);
    setTriggerMotionCeasedTime_ms(10000);
    
    dateAndTimeWrite(2023, 6, 13, 16, 47, 1);

    setFunctionalTimePeriod();
}

void energySaveSystemUpdate()
{
    static int motionTimer = 0;

    if(isFunctionalTime()) {
        functionalTimeLed = ON;
    } else {
        functionalTimeLed = OFF;
    }

    actuatorUpdate();

    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
