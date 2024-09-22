// ask_transmitter.ino
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int k;

// RH_ASK driver;
// pin 5 for output
RH_ASK driver(2000, 0, 10, 0); // Mega2560   transmitter pin #10
// RH_ASK driver(2000, 0, 2, 0); //  arduino Micro, does not work neither with pin #2 nor #10
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS

void setup()
{
Serial.print("starting setup");
delay(200);

#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif

if (!driver.init())
#ifdef RH_HAVE_SERIAL
   Serial.print("init failed");
#else
	 Serial.print("no init success");
#endif
Serial.print("  end\n");
// Serial.flush();
k=0;
}

void loop()
{   /* the main loop sends a string consisting of a number which is
       incremented in the loop and the constant string 'hello'
       you can use the serial monitor of the IDE to watch how the
       counter variable is incremented
   */
    const char *msg = "  hello";
    // Determine the size required for the final message
    // Maximum length of integer as string + length of original message + 1 for null terminator
    int final_size = snprintf(NULL, 0, "%d%s", k, msg) + 1;
    
    // Allocate memory for the new message
    char *new_msg = (char *)malloc(final_size);
    
    // Create the new message by formatting the integer and original string
    snprintf(new_msg, final_size, "%d%s", k, msg);
    
    driver.send((uint8_t *)new_msg, strlen(new_msg));
    driver.waitPacketSent();
    delay(200);
    Serial.print(k);
    k++;

    // Properly delete the pointer otherwise you end up 
    // using all availabel memory and the program crashes
    delete[] new_msg;
    // Set to null after deletion to avoid dangling pointer
    new_msg = nullptr;
    
}
