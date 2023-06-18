/*! @file energy_save_system.h Header file for the integrated system module.
 *
 * @note This module integrates all other modules.
 */

//=====[#include guards - begin]===============================================

#ifndef _ENERGY_SAVE_SYSTEM_H_
#define _ENERGY_SAVE_SYSTEM_H_

//=====[Declaration of public defines]=========================================

// Mainloop dt is 1 ms so the bluetooth serial com does not miss any data.
#define SYSTEM_TIME_INCREMENT_MS 1   ///> Time interval for mainloop.

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes the system.
 * 
 */
void energySaveSystemInit();

/**
 * @brief Updates the modules.
 * 
 */
void energySaveSystemUpdate();

//=====[#include guards - end]=================================================

#endif // _ENERGY_SAVE_SYSTEM_H_