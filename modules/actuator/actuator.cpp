/*! @file actuator.cpp Implementation of the actuator module.
 *
 */

//=====[Libraries]=============================================================

#include "actuator.h"

#include "mbed.h"

#include "motion_sensor.h"
#include "relay_control.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

#define ON_BUTTON PB_1
#define OFF_BUTTON PC_2

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn onButton(ON_BUTTON);
DigitalIn offButton(OFF_BUTTON);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

int dt_ms;  ///> Time increment to update module.
int TriggerCeasedMotionTime = -1; ///> Time to deactivate relay once motion is not detected.
bool motionSensorEnable = true; ///> Enable of the motion sensor.

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void actuatorInit(int dt)
{
    printf("%s\n", "Initializing program."); // Debug.

    dt_ms = dt;

    motionSensorInit(dt);
    relayControlInit();

    printf("%s\n", "Inizialitation complete."); // Debug.
}

void actuatorUpdate()
{
    motionSensorEnable = isFunctionalTime();

    if(TriggerCeasedMotionTime <= 0 || !(motionSensorEnable)) {
        motionSensorUpdate();
        relayActivate();
        return;
    }

    int CeasedMotionTime = motionSensorUpdate();

    if(CeasedMotionTime >= TriggerCeasedMotionTime) {
        relayDeactivate();
    } else {
        relayActivate();
    }
}

void setTriggerMotionCeasedTime_ms(int time_ms)
{
    if(time_ms <= 0) {
        TriggerCeasedMotionTime = time_ms;
    } else {
        TriggerCeasedMotionTime = time_ms;
    }
}

//=====[Implementations of private functions]==================================