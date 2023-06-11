/*! @file relay_control.cpp Implementation of the relay control module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"

#include "arm_book_lib.h"

#include "relay_control.h"

//=====[Declaration of private defines]========================================

#define RELAY_PIN PF_2  ///> Relay control pin.

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalInOut relayPin(RELAY_PIN);   ///> DigitalInOut relay pin.

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool relayStatus;   ///> Relay status boolean variable.

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void relayControlInit()
{
    relayPin.mode(OpenDrain);
    relayDeactivate();
}

void relayActivate()
{
    relayPin.output();
    relayPin = LOW;
    relayStatus = ON;
}

void relayDeactivate()
{
    relayPin.input();
    relayStatus = OFF;
}

//=====[Implementations of private functions]==================================
