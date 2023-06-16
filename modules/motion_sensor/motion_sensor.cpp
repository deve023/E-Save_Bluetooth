/*! @file motion_sensor.cpp Implementation of the motion sensor module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"

#include "arm_book_lib.h"

#include "motion_sensor.h"

#define SIGNAL_PIN PG_0 ///> Sensor signal pin define.
#define MOTION_SENSOR_LED_PIN LED1 // PB_0

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn motionSensorOutputSignal(SIGNAL_PIN);   ///> Sensor signal pin.
DigitalOut motionSensorLed(MOTION_SENSOR_LED_PIN);  ///> Led to indicate sensor status.

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool motionSensorState;  ///> Sensor state: ON/OFF.

static int dt_ms = 0;   ///> Time increment to update accumulated ceased motion time.

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motionSensorInit(int dt)
{
    dt_ms = dt;
    motionSensorState = OFF;
    motionSensorLed = OFF;
}

bool motionSensorRead()
{
    return motionSensorState;
}

int motionSensorUpdate()
{
    static int accumulatedMotionCeasedTime = 0;

    if(motionSensorOutputSignal == ON) {
        motionSensorState = ON;
        motionSensorLed = ON;
        accumulatedMotionCeasedTime = 0;
    } else {
        motionSensorState = OFF;
        motionSensorLed = OFF;
        accumulatedMotionCeasedTime += dt_ms;
    }

    return accumulatedMotionCeasedTime;
}

//=====[Implementations of private functions]==================================