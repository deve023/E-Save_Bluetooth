/*! @file ble_com.cpp Implementation of the Bluetooth Comunication module.
 *
 */

//=====[Libraries]=============================================================

#include "ble_com.h"

#include "mbed.h"

#include "actuator.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

#define RX PD_5
#define TX PD_6
#define BLE_COM_BAUDRATE 9600

//=====[Declaration of private data types]=====================================

typedef enum {
    BLE_IDLE
} bleComState_t;

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial bleCom(RX, TX, BLE_COM_BAUDRATE);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

bleComState_t bleComState = BLE_IDLE;

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Receives char from Bluetooh communication if there is a char to be read.
 * 
 * @return read char. If nothing to be read: returns '\0'.
 */
static char bleComCharRead();

/**
 * @brief Sets default date and time values and Functional time period as well.
 * 
 */
static void setDefaultDateAndTimeValues();

//=====[Implementations of public functions]===================================

void bleComInit()
{
    setDefaultDateAndTimeValues();
}

void bleComUpdate()
{
    char c = bleComCharRead();
    if(c != '\0') {
        switch(bleComState) {
            case BLE_IDLE:
                break;
            default:
                bleComState = BLE_IDLE;
        }
    }
}

//=====[Implementations of private functions]==================================

static char bleComCharRead()
{
    char c = '\0';
    if(bleCom.readable()) {
        bleCom.read(&c,1);
    }
    return c;
}

static void setDefaultDateAndTimeValues()
{
    dateAndTimeWrite(DATE_AND_TIME_DEFAULT);
    setFunctionalTimePeriod();
}