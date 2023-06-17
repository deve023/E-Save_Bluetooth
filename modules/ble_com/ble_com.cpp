/*! @file ble_com.cpp Implementation of the Bluetooth Comunication module.
 *
 */

//=====[Libraries]=============================================================

#include "ble_com.h"

#include "mbed.h"

#include "actuator.h"
#include "date_and_time.h"

//=====[Declaration of private defines]========================================

#define RX USBRX //PD_5
#define TX USBTX //PD_6
#define BLE_COM_BAUDRATE 9600

#define DATE_AND_TIME_NUMBER_OF_CHARS 14
#define FUNCTIONAL_TIME_NUMBER_OF_CHARS 12

//=====[Declaration of private data types]=====================================

typedef enum {
    BLE_PROCESS_COMMAND,
    BLE_SET_DATE_TIME,
    BLE_SET_FUNCTIONAL_TIME,
    BLE_SET_TRIG_TIME
} bleComState_t;

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial bleCom(TX, RX, BLE_COM_BAUDRATE);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

static bleComState_t bleComState = BLE_PROCESS_COMMAND;

static char newDateAndTime[DATE_AND_TIME_NUMBER_OF_CHARS];
static char newFunctionalTime[FUNCTIONAL_TIME_NUMBER_OF_CHARS];
static char newTrigTime[50];

static char aux[50];

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Receives char from Bluetooh communication if there is a char to be read.
 * 
 * @return read char. If nothing to be read: returns '\0'.
 */
static char bleComCharRead();

/**
 * @brief Transmits a string through Bluetooth.
 * 
 * @param[in] s String to send.
 */
static void bleComStringWrite(const char* s);

/**
 * @brief Sets default date and time values and Functional time period as well.
 * 
 */
static void setDefaultDateAndTimeValues();

/**
 * @brief Process received command.
 * 
 * @param[in] c Command to process.
 */
static void bleProcessCommand(char c);

/**
 * @brief Explain acceptabl commands to process.
 * 
 */
static void printAcceptableCommands();

/**
 * @brief Process received command.
 * 
 * @param[in] c Command to process.
 */
static void bleProcessCommand(char c);

/**
 * @brief Initiates process of setting new date and time.
 * 
 */
static void bleCommandNewDateAndTime();

/**
 * @brief Gets new char for the new date and time.
 * 
 * @param[in] c new char from the date and time.
 */
static void bleComDateAndTimeUpdate(char c);

/**
 * @brief Sets new date and time according to variable newDateAndTime[].
 * 
 */
static void bleComSetDateAndTime();

/**
 * @brief Sends current date and time.
 * 
 */
static void bleCommandPrintDateAndTime();

/**
 * @brief Initiates process of setting new trig time.
 * 
 */
static void bleCommandNewTrigTime();

/**
 * @brief Gets new char for the new date and time.
 * 
 * @param[in] c new char from the date and time.
 */
static void bleComNewTrigUpdate(char c);

/**
 * @brief Sets new date and time according to variable newDateAndTime[].
 * 
 * @param[in] n Number of characters input by user.
 */
static void bleComSetNewTrigTime(int n);

/**
 * @brief Sends current trigger time.
 * 
 */
static void bleCommandPrintTrigTime();

/**
 * @brief Initiates process of setting new functional time.
 * 
 */
static void bleCommandNewFunctionalTime();

/**
 * @brief Gets new char for the new functional time.
 * 
 * @param[in] c new char for the new functional time.
 */
static void bleComFunctionalTimeUpdate(char c);

/**
 * @brief Sets new functional time according to variable newFunctionalTime[].
 * 
 */
static void bleComSeFunctionalTime();

/**
 * @brief Prints the functional time period.
 * 
 */
static void bleCommandPrintFunctionalTime();

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
            case BLE_PROCESS_COMMAND:
                bleProcessCommand(c);
                break;
            case BLE_SET_DATE_TIME:
                bleComDateAndTimeUpdate(c);
                break;
            case BLE_SET_FUNCTIONAL_TIME:
                bleComFunctionalTimeUpdate(c);
                break;
            case BLE_SET_TRIG_TIME:
                bleComNewTrigUpdate(c);
                break;
            default:
                bleComState = BLE_PROCESS_COMMAND;
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
    setFunctionalTimePeriod(FUNCTIONAL_TIME_DEFAULT);
}

static void bleProcessCommand(char c)
{
    switch(c) {
        case '1':
            bleCommandNewTrigTime();
            break;
        case '2':
            bleCommandPrintTrigTime();
            break;
        case '3':
            bleCommandNewFunctionalTime();
            break;
        case '4':
            bleCommandPrintFunctionalTime();
            break;
        case '5':
            bleCommandNewDateAndTime();
            break;
        case '6':
            bleCommandPrintDateAndTime();
            break;
        case 'h':
            printAcceptableCommands();
            break;
        default:
            bleComStringWrite("Command not understood. Please review acceptable commands:\r\n");
            printAcceptableCommands();
    }
}

static void bleComStringWrite(const char* s)
{
    bleCom.write(s, strlen(s));
}

static void printAcceptableCommands()
{
    bleComStringWrite("Acceptable commands:\r\n");
    bleComStringWrite("Send '1' to set trigger time.\r\n");
    bleComStringWrite("Send '2' to get current trigger time.\r\n");
    bleComStringWrite("Send '3' to set funcional period.\r\n");
    bleComStringWrite("Send '4' to get funcional period.\r\n");
    bleComStringWrite("Send '5' to set date and time.\r\n");
    bleComStringWrite("Send '6' to get current date and time.\r\n");
    bleComStringWrite("Send 'h' for help.\r\n");
    bleComStringWrite("\r\n");
}

static void bleCommandNewDateAndTime()
{
    bleComStringWrite("\r\nType four digits for the current year (YYYY): ");
    bleComState = BLE_SET_DATE_TIME;
}

static void bleComDateAndTimeUpdate(char c)
{
    static int numberOfDateAndTimeChar = 0;

    newDateAndTime[numberOfDateAndTimeChar++] = c;

    sprintf(aux, "%c", c);
    bleComStringWrite(aux);

    if(numberOfDateAndTimeChar >= DATE_AND_TIME_NUMBER_OF_CHARS) {
        bleComState = BLE_PROCESS_COMMAND;
        numberOfDateAndTimeChar = 0;
        bleComSetDateAndTime();
        bleComStringWrite("\r\n");
        bleComStringWrite("Date and time has been set.\r\n");
    } else if(numberOfDateAndTimeChar == 4) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the current month (01-12): ");
    } else if(numberOfDateAndTimeChar == 6) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the current day (01-31): ");
    } else if(numberOfDateAndTimeChar == 8) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the current hour (00-23): ");
    } else if(numberOfDateAndTimeChar == 10) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the current minutes (00-59): ");
    } else if(numberOfDateAndTimeChar == 12) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the current seconds (00-59): ");
    }
}

static void bleComSetDateAndTime()
{
    char year[5];
    char month[3];
    char day[3];
    char hour[3];
    char minute[3];
    char second[3];

    for(int i = 0; i < DATE_AND_TIME_NUMBER_OF_CHARS; i++) {
        if(i < 4)
            year[i] = newDateAndTime[i];
        else if(i < 6) {
            month[i-4] = newDateAndTime[i];
        } else if(i < 8) {
            day[i-6] = newDateAndTime[i];
        } else if(i < 10) {
            hour[i-8] = newDateAndTime[i];
        } else if(i < 12) {
            minute[i-10] = newDateAndTime[i];
        } else {
            second[i-12] = newDateAndTime[i];
        }
    }
    year[4] = '\0';
    month[2] = '\0';
    day[2] = '\0';
    hour[2] = '\0';
    minute[2] = '\0';
    second[2] = '\0';

    dateAndTimeWrite(atoi(year), atoi(month), atoi(day), 
        atoi(hour), atoi(minute), atoi(second));
}

static void bleCommandPrintDateAndTime()
{
    bleComStringWrite("Current date and time: ");
    bleComStringWrite(dateAndTimeRead());
    bleComStringWrite("\r\n");
}

static void bleCommandPrintTrigTime()
{
    bleComStringWrite("Current trigger time: ");

    sprintf(aux, "%d", getTriggerTime_ms() / 3600000);
    bleComStringWrite(aux);
    bleComStringWrite("h ");

    sprintf(aux, "%d", (getTriggerTime_ms()%3600000) / 60000);
    bleComStringWrite(aux);
    bleComStringWrite("m ");

    sprintf(aux, "%d", (getTriggerTime_ms() % 60000)/1000);
    bleComStringWrite(aux);
    bleComStringWrite(" s.\r\n");
}

static void bleCommandNewTrigTime()
{
    bleComStringWrite("\r\nType required wait time followed by 'h', 'm' or 's' to indicate unit of measurement: ");
    bleComState = BLE_SET_TRIG_TIME;
}

static void bleComNewTrigUpdate(char c)
{
    static int numberOfTrigTimeChar = 0;

    newTrigTime[numberOfTrigTimeChar++] = c;

    sprintf(aux, "%c", c);
    bleComStringWrite(aux);

    switch(c){
        case 'h':
        case 'm':
        case 's':
            bleComSetNewTrigTime(numberOfTrigTimeChar);
            numberOfTrigTimeChar = 0;
            bleComState = BLE_PROCESS_COMMAND;
            bleComStringWrite("\r\n");
            bleComStringWrite("Trigger wait time has been set.\r\n");
        default:
            break;
    }

}

static void bleComSetNewTrigTime(int n)
{
    int i, inputTrigTime;

    for(i = 0; i < n-1; i++) {
        aux[i] = newTrigTime[i];
    }
    aux[i] = '\0';

    inputTrigTime = atoi(aux);

    switch(newTrigTime[n-1]) {
        case 'h':
            setTriggerMotionCeasedTime_ms(inputTrigTime * 3600000);
            break;
        case 'm':
            setTriggerMotionCeasedTime_ms(inputTrigTime * 60000);
            break;
        case 's':
            setTriggerMotionCeasedTime_ms(inputTrigTime * 1000);
            break;
        default:
            bleComStringWrite("Your input was not understood. Set trig time to default: 3 seconds.");
            setTriggerMotionCeasedTime_ms(3000);
            break;
    }
}

static void bleCommandNewFunctionalTime()
{
    bleComStringWrite("\r\nType two digits for the start hour (00-23): ");
    bleComState = BLE_SET_FUNCTIONAL_TIME;
}

static void bleComFunctionalTimeUpdate(char c)
{
    static int numberOfFunctionalTimeChar = 0;

    newFunctionalTime[numberOfFunctionalTimeChar++] = c;

    sprintf(aux, "%c", c);
    bleComStringWrite(aux);

    if(numberOfFunctionalTimeChar >= FUNCTIONAL_TIME_NUMBER_OF_CHARS) {
        bleComState = BLE_PROCESS_COMMAND;
        numberOfFunctionalTimeChar = 0;
        bleComSeFunctionalTime();
        bleComStringWrite("\r\n");
        bleComStringWrite("Functional time has been set.\r\n");
    } else if(numberOfFunctionalTimeChar == 2) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the start minute (00-59): ");
    } else if(numberOfFunctionalTimeChar == 4) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the start second (00-59): ");
    } else if(numberOfFunctionalTimeChar == 6) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the finish hour (00-23): ");
    } else if(numberOfFunctionalTimeChar == 8) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the finish minutes (00-59): ");
    } else if(numberOfFunctionalTimeChar == 10) {
        bleComStringWrite("\r\n");
        bleComStringWrite("Type two digits for the finish seconds (00-59): ");
    }
}

static void bleComSeFunctionalTime()
{
    char sHour[3];
    char sMin[3];
    char sSec[3];
    char eHour[3];
    char eMin[3];
    char eSec[3];

    for(int i = 0; i < DATE_AND_TIME_NUMBER_OF_CHARS; i++) {
        if(i < 2)
            sHour[i] = newFunctionalTime[i];
        else if(i < 4) {
            sMin[i-2] = newFunctionalTime[i];
        } else if(i < 6) {
            sSec[i-4] = newFunctionalTime[i];
        } else if(i < 8) {
            eHour[i-6] = newFunctionalTime[i];
        } else if(i < 10) {
            eMin[i-8] = newFunctionalTime[i];
        } else {
            eSec[i-10] = newFunctionalTime[i];
        }
    }
    sHour[2] = '\0';
    sMin[2] = '\0';
    sSec[2] = '\0';
    eHour[2] = '\0';
    eMin[2] = '\0';
    eSec[2] = '\0';

    setFunctionalTimePeriod(atoi(sHour), atoi(sMin), atoi(sSec), atoi(eHour), atoi(eMin), atoi(eSec));
}

static void bleCommandPrintFunctionalTime()
{
    int v[6];
    functionalTimeRead(v);

    sprintf(aux,"Functional time start: %d:%d:%d.\r\n", v[0], v[1], v[2]);
    bleComStringWrite(aux);
    sprintf(aux,"Functional time end: %d:%d:%d.\r\n", v[3], v[4], v[5]);
    bleComStringWrite(aux);
}