/*! @file actuator.h Header file for the actuator module.
 *
 * @note This module handles the sensor and control actuators.
 * It implements the control logic and updates sensor and relay.
 */

//=====[#include guards - begin]===============================================

#ifndef _ACTUATOR_H_
#define _ACTUATOR_H_

//=====[Declaration of public defines]========================================

#define TRIGGER_TIME_DEFAULT 5000   ///> Default trigger time: 5 seconds.

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initialices actuator.
 * 
 * Initial state: disabled (updated as soon as actuatorUpdate() is called).
 * Default trigger time: 5 seconds.
 */
void actuatorInit(int dt);

/**
 * @brief Updates actuator: sensors and relay.
 * 
 */
void actuatorUpdate();

/**
 * @brief Sets the time to deactivate relay once motion is not detected.
 * 
 * @param[in] time_ms time in miliseconds to deactivate relay once motion is not detected.
 */
void setTriggerMotionCeasedTime_ms(int time_ms);

/**
 * @brief Returns the time set to deactivate relay once motion is not detected.
 * 
 * @return Trigger time in miliseconds.
 */
int getTriggerTime_ms();

//=====[#include guards - end]=================================================

#endif // _ACTUATOR_H_