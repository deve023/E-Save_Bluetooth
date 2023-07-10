![logo](https://github.com/deve023/E-Save_Bluetooth/assets/51866497/d53e6131-77cd-44be-862a-953f828b7288)

E-Save Bluetooth is a low cost device which turns an electric appliance off if it does not detect presence in its environment for a certain period of time. It can be configured via Bluetooth Low Energy. The product consists of a main arm microcontroler (included in the NUCLEO F429ZI board) connected to a motion sensor and a relay. The board also communicates with an HM-10 board through its serial port in order to support BLE communication. Users can configure the system using the Serial Bluetooth Terminal app.

![eSaveB_portada (1)](https://github.com/deve023/E-Save_Bluetooth/assets/51866497/6fa726ec-ec9c-4e5e-b631-99bab9df0271)

This project was developed as part of the Embedded Systems course in the University of Buenos Aires. I designed and implemented a prototype while in my last year of studying Electronic Engineering. I believe anyone with basic knowledge in electronics and embedded software can understand and implement this device. Developing and building this prototype took approximately 20 hours of work spread over 4 weeks.

Video summary (English): [Youtube](https://youtu.be/3YbzRw6OTMo)

Video Demo (Spanish): [Youtube](https://youtu.be/fHSL6gb9g30)

Summary (Spanish): [PDF](https://docs.google.com/document/d/1ngRxoOGkS6Whcuwp6-DJUADUrxsZ91UcAmCLxtPNpU8/edit)

# Background

The idea for this product comes from the fact that having a high consumption appliance on for unnecessary long periods of time can be very dangerous and expensive. In this day and age, it’s of the upmost importance to regulate electrical consumption at home. E-Save Bluetooth was developed in order to diminish negative impact to the environment and also help save money on the electrical bill.

The product stands out from what the market currently offers due to its low cost and diverse functionality. It comes with an innovative feature: a motion sensor to detect when there is no one around in the room and turns off the appliance so it does not needlessly waste energy. In contrast, smart thermostats and smart plugs work only with timers, they do not sense the environment. Regarding cost, there is a considerable price difference between a smart plug (low-cost: 12 USD) and a smart thermostat (around 360 USD). E-Save Bluetooth conveniently positions itself between them at a low-cost of 40 USD per unit.

# File system

The firmware consists of 6 modules. The Energy Save system encapsulates the whole logic. Two main subsystems, actuator and ble_com, implement the most complex FSM (Finite-State Machines). The two systems run "in parallel" and at the same time interact with one another. There are two driver modules (for the relay and sensor) and a module to handle the RTC (Real Time Clock). I recommend perusing the written code in order to familirize yourself with state machines, if you have not already done so. FSM are a highly effective way to develope code for a project with many modules running simultaneously.

![ESave-Files Diagram drawio](https://github.com/deve023/E-Save_Bluetooth/assets/51866497/99ead2e6-de79-4c60-9c10-bc97c4bf643c)

# Bill of materials

* NUCLEO F429ZI board.
* Relay module 220Vac 10A (Validate max current according to the electric appliance to be connected).
* Motion sensor (I used an infrared PIR sensor for the prototype, it's limited but also cheap. I recommend investigating a bit in order to buy the best option for you).
* HM-10 Bluetooth module.
* BC547 (It's a good idea to but a buffer in between the board and the relay module. This is a very accesible NPN).
* 10 kΩ resistor to polarize the BC547.
* 6 LEDs (3 reds, 1 yellow, 1 green, 1 blue).
* 150 Ω to polarize the LEDs.
* 2 buttons.

# Circuit diagram

![ESave-Overview_Pins drawio (2)](https://github.com/deve023/E-Save_Bluetooth/assets/51866497/7a885e3e-80d0-439a-9be5-da4d1856e8ee)

Feel free to contact me if you have any questions or ideas!
