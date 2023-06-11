/*! @file energy_save_system.cpp Implementation of the system module.
 *
 */

//=====[Libraries]=============================================================

#include "../arm_book_lib.h"

#include "energy_save_system.h"

#include "motion_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void smartHomeSystemInit()
{
    //TODO
    motionSensorInit();
}

void smartHomeSystemUpdate()
{
    //TODO
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
