/*! @file motion_sensor.h Header file for the motion sensor module.
 *
 * @note This module encapsulates the behaivor of the motion sensor.
 */

//=====[#include guards - begin]===============================================

#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes motion sensor. Sensor deactivated.
 * 
 */
void motionSensorInit();

/**
 * @brief Reads sensor state.
 * 
 * @return Boolean to indicate sensor state being ON/OFF.
 */
bool motionSensorRead();

/**
 * @brief Activates motion sensor.
 * 
 */
void motionSensorActivate();

/**
 * @brief Deactivates motion sensor.
 * 
 */
void motionSensorDeactivate();

//=====[#include guards - end]=================================================

#endif // _MOTION_SENSOR_H_