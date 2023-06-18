/*! @mainpage E-Save Bluetooth 
 * @date Saturday, June 3, 2023
 * @authors Agustin de Vedia
 *
 * @file main.cpp Main program script for NUCLEO F429ZI board.
 * Refer to modules\ for the implementation of the modules.
 *
 * @note Program is designed to run in a NUCLEO F429ZI board.
 * Refer to README for more a detailed description.
 */

//=====[Libraries]=============================================================

#include "energy_save_system.h" ///> System module.

//=====[Main function, the program entry point after power on or reset]========

/**
 * @brief Main function. Setup & main loop.
 * 
 */
int main()
{
    // Setup:
    energySaveSystemInit();

    // Mainloop:
    while (true) {
        energySaveSystemUpdate();
    }
}