/*! @file energy_save_system.h Header file for the system module.
 *
 * @note This module integrates all other modules.
 */

//=====[#include guards - begin]===============================================

#ifndef _ENERGY_SAVE_SYSTEM_H_
#define _ENERGY_SAVE_SYSTEM_H_

//=====[Declaration of public defines]=========================================

#define SYSTEM_TIME_INCREMENT_MS   10   ///> Time interval for mainloop.

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes modules.
 * 
 */
void energySaveSystemInit();

/**
 * @brief Updates modules.
 * 
 */
void energySaveSystemUpdate();

//=====[#include guards - end]=================================================

#endif // _ENERGY_SAVE_SYSTEM_H_