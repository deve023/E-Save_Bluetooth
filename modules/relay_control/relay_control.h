/*! @file relay_control.h Header file for the motion sensor module.
 *
 * @note This module encapsulates the behaivor of the relay control to
 * turn on/off the connected electric appliance.
 */

//=====[#include guards - begin]===============================================

#ifndef _RELAY_CONTROL_H_
#define _RELAY_CONTROL_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initialices relay pin and state.
 * 
 * Relay initial state: activated.
 */
void relayControlInit();

/**
 * @brief Activates relay.
 * 
 */
void relayActivate();

/**
 * @brief Deactivates relay.
 * 
 */
void relayDeactivate();

//=====[#include guards - end]=================================================

#endif // _MOTION_SENSOR_H_