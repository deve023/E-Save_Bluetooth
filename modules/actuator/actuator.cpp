/*! @file actuator.cpp Implementation of the actuator module.
 *
 */

//=====[Libraries]=============================================================

#include "actuator.h"

#include "mbed.h"
#include "arm_book_lib.h"

#include "motion_sensor.h"
#include "relay_control.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

#define ON_BUTTON PB_1  ///> Button to turn actuator logic on.
#define OFF_BUTTON PC_2 ///> Button to turn actuator logic off: relay disconected regardless of time / sensor status.

//=====[Declaration of private data types]=====================================

typedef enum {
    ACTUATOR_DISABLE,
    ACTUATOR_MOTION_DETECTED,
    ACTUATOR_MOTION_CEASED,
    ACTUATOR_RELAY_DEACTIVATED
} actuatorState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn onButton(ON_BUTTON);      ///> On button (Button to turn actuator logic on).
DigitalIn offButton(OFF_BUTTON);    ///> Off button (Button to turn actuator logic off: relay disconected regardless of time / sensor status).

DigitalOut functionalTimeLed(LED2); ///> Led to indicate if the current time is a functional time.

//=====[Declaration and initialization of public global variables]=============

static int dt_ms;  ///> Time increment to update module.
static int TriggerCeasedMotionTime; ///> Time to deactivate relay once motion is not detected. Default = 3 seg.
static actuatorState_t actuatorState = ACTUATOR_DISABLE;   ///> Initial state of the Actuator. Updated as soon as actuatorUpdate() is called.

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Handler for the ON button interrupt.
 * 
 */
static void onButtonPressed();

/**
 * @brief Handler for the OFF button interrupt.
 * 
 */
static void offButtonPressed();

//=====[Implementations of public functions]===================================

void actuatorInit(int dt)
{
    dt_ms = dt;
    TriggerCeasedMotionTime = TRIGGER_TIME_DEFAULT;

    motionSensorInit(dt);
    relayControlInit();
}

void actuatorUpdate()
{
    int CeasedMotionTime = motionSensorUpdate(); // Regardless of Actuator state, the sensor needs to be updated.

    if(!isFunctionalTime()) {
        actuatorState = ACTUATOR_DISABLE;
        functionalTimeLed = OFF;
    }

    switch(actuatorState) {
        case ACTUATOR_DISABLE:
            if(isFunctionalTime()) {
                if(CeasedMotionTime > 0) {
                    actuatorState = ACTUATOR_MOTION_CEASED;
                } else {
                    actuatorState = ACTUATOR_MOTION_DETECTED;
                }
                functionalTimeLed = ON;
            }
            relayActivate();
            break;
        case ACTUATOR_MOTION_DETECTED:
            if(CeasedMotionTime > 0) {
                actuatorState = ACTUATOR_MOTION_CEASED;
            }
            relayActivate();
            break;
        case ACTUATOR_MOTION_CEASED:
            if(CeasedMotionTime == 0) {
                actuatorState = ACTUATOR_MOTION_DETECTED;
            } else if(CeasedMotionTime >= TriggerCeasedMotionTime) {
                actuatorState = ACTUATOR_RELAY_DEACTIVATED;
            }
            break;
        case ACTUATOR_RELAY_DEACTIVATED:
            if(CeasedMotionTime == 0) {
                actuatorState = ACTUATOR_MOTION_DETECTED;
            }
            relayDeactivate();
            break;
        default:
            actuatorState = ACTUATOR_DISABLE;
    }

}

void setTriggerMotionCeasedTime_ms(int time_ms)
{
    if(time_ms > 0) {
        TriggerCeasedMotionTime = time_ms;
    } else {
        TriggerCeasedMotionTime = TRIGGER_TIME_DEFAULT;
    }
}

int getTriggerTime_ms()
{
    return TriggerCeasedMotionTime;
}
