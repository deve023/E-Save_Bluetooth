/*! @file energy_save_system.cpp Implementation of the system module.
 *
 */

//=====[Libraries]=============================================================

#include "energy_save_system.h"

#include "arm_book_lib.h"

#include "actuator.h"
#include "ble_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void energySaveSystemInit()
{
    actuatorInit(SYSTEM_TIME_INCREMENT_MS);
    bleComInit();
}

void energySaveSystemUpdate()
{
    actuatorUpdate();
    bleComUpdate();

    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
