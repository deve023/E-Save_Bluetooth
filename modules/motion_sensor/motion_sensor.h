/*! @file motion_sensor.h Header file for the motion sensor module.
 *
 * @note This module encapsulates the behaivor of the motion sensor.
 */

//=====[#include guards - begin]===============================================

#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes motion sensor.
 * 
 */
void motionSensorInit(int dt);

/**
 * @brief Updates and returns the accumulated time that the sensor did not
 * detect motion.
 *
 * @return Accumulated non motion detected time in miliseconds.
 */
int motionSensorUpdate();

//=====[#include guards - end]=================================================

#endif // _MOTION_SENSOR_H_