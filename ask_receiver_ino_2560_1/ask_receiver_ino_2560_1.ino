// ask_receiver.pde
// -*- mode: C++ -*-
/*
# Copyright 2024 Juergen Humt
# 
# This file is part of project ask_433RF.
# 
#
#     ask_433RF, is free  software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by the 
#     Free Software Foundation, either version 3 of the License or any later 
#     version.
# 
#     ask_433RF is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
# 
#     You should have received a copy of the GNU General Public License along 
#     with ask_433RF.  If not, see <http://www.gnu.org/licenses/>.
*/

// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with a  QITA QT08012 module
// Tested on Arduino Mega, micro (see Read.me)

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

int ledState = HIGH;       // ledState used to set the LED
long kC;
const int ledPin = 11;     // the number of the LED pin

// RH_ASK driver;
RH_ASK driver(2000, 5, 0, 0); // 
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS

void setup() {
pinMode(ledPin, OUTPUT);
ledState = HIGH;
digitalWrite(ledPin, ledState);
ledState = LOW;
delay(2000);
digitalWrite(ledPin, ledState);
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif

if (!driver.init())
#ifdef RH_HAVE_SERIAL
  Serial.println("init failed");
#else
	;
#endif
kC =0;
}

void loop()
{

  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);


  // for (int k=0; k<7; k++) {
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    // delay(300);
    // digitalWrite(ledPin, ledState);
    // }


    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	// Message with a good checksum received, dump it.
	     driver.printBuffer("Got:", buf, buflen);
       digitalWrite(ledPin, ledState);       
    }
}
