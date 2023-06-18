/*! @file energy_save_system.cpp Implementation of the integrated system module.
 *
 */

//=====[Libraries]=============================================================

#include "energy_save_system.h"

#include "arm_book_lib.h"

#include "actuator.h"
#include "ble_com.h"

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

