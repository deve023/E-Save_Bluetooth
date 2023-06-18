/*! @file relay_control.cpp Implementation of the relay control module.
 *
 */

//=====[Libraries]=============================================================

#include "mbed.h"

#include "arm_book_lib.h"

#include "relay_control.h"

//=====[Declaration of private defines]========================================

#define RELAY_PIN PF_2  ///> Relay control pin.

#define RELAY_ACT_LED_PIN LED3      ///> LED pin to indicate relay active.
#define RELAY_DEACT_LED_PIN PH_1    //> LED pin to indicate relay inactive.

//=====[Declaration and initialization of public global objects]===============

DigitalInOut relayPin(RELAY_PIN);   ///> Relay control pin.

DigitalOut relayActLed(RELAY_ACT_LED_PIN);      ///> LED to indicate relay activate.
DigitalOut relayDeactLed(RELAY_DEACT_LED_PIN);  ///> LED to indicate relay inactive.

//=====[Declaration and initialization of private global variables]============

static bool relayStatus;   ///> Relay status boolean variable.

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

    relayActLed = ON;
    relayDeactLed = OFF;
}

void relayDeactivate()
{
    relayPin.input();
    relayStatus = OFF;

    relayActLed = OFF;
    relayDeactLed = ON;
}

//=====[Implementations of private functions]==================================
