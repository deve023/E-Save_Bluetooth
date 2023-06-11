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

InterruptIn motionSensorOutputSignal(SIGNAL_PIN);   ///> Sensor signal pin.
DigitalOut motionSensorLed(MOTION_SENSOR_LED_PIN);  ///> Led to indicate sensor status.

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool motionSensorState;  ///> Sensor state: ON/OFF.
static bool motionSensorActivated;  ///> Boolean to indicate if sensor is active.

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Updates status to reflect motion sensor being triggered.
 * 
 */
static void motionDetected();

/**
 * @brief Updates status to reflect motion sensor no longer being triggered.
 * 
 */
static void motionCeased();

//=====[Implementations of public functions]===================================

void motionSensorInit()
{
    motionSensorOutputSignal.rise(&motionDetected);
    motionSensorState = OFF;
    motionSensorActivated = false;
    motionSensorLed = OFF;
}

bool motionSensorRead()
{
    return motionSensorState;
}

void motionSensorActivate()
{
    motionSensorActivated = true;
    if ( !motionSensorState ) {
        motionSensorOutputSignal.rise(&motionDetected);
    }
}

void motionSensorDeactivate()
{
    motionSensorActivated = false;
    if ( !motionSensorState ) {
        motionSensorOutputSignal.rise(NULL);
    }
}

//=====[Implementations of private functions]==================================

static void motionDetected()
{
    motionSensorState = ON;
    motionSensorOutputSignal.rise(NULL);
    motionSensorOutputSignal.fall(&motionCeased);
    motionSensorLed = ON;
}

static void motionCeased()
{
    motionSensorState = OFF;
    motionSensorOutputSignal.fall(NULL);
    if ( motionSensorActivated ) {
        motionSensorOutputSignal.rise(&motionDetected);
    }
    motionSensorLed = OFF;
}
