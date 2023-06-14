/*! @file actuator.h Header file for the actuator module.
 *
 * @note This module handless the sensor and control actuators.
 * It implements the control logic and updates sensor and relay.
 */

//=====[#include guards - begin]===============================================

#ifndef _ACTUATOR_H_
#define _ACTUATOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initialices actuator.
 * 
 */
void actuatorInit(int dt);

/**
 * @brief Updates actuator. Sensors and relay.
 * 
 */
void actuatorUpdate();

/**
 * @brief Sets the time to deactivate relay once motion is not detected.
 * 
 */
void setTriggerMotionCeasedTime_ms(int time_ms);

//=====[#include guards - end]=================================================

#endif // _ACTUATOR_H_