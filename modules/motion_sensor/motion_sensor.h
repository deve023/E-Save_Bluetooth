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
void motionSensorInit(int dt);

/**
 * @brief Reads sensor state.
 * 
 * @return Boolean to indicate sensor state being ON/OFF.
 */
bool motionSensorRead();

/**
 * @brief Updates and returns the accumulated time that the sensor did not
 * detect motion.
 *
 * @return Accumulated non motion detected time.
 */
int motionSensorUpdate();

//=====[#include guards - end]=================================================

#endif // _MOTION_SENSOR_H_