//*******************************************************************
// owbus.cpp
// from Project https://github.com/mchresse/BeeIoT
//
// Description:
// Contains main setup() and helper() routines for OneWire bus connected
// devices.
// See also at https://randomnerdtutorials.com/esp32-multiple-ds18b20-temperature-sensors/
//
//-------------------------------------------------------------------
// Copyright (c) 2019-present, Randolph Esser
// All rights reserved.
// This file is distributed under the BSD-3-Clause License
// The complete license agreement can be obtained at:
//     https://github.com/mchresse/BeeIoT/license
// For used 3rd party open source see also Readme_OpenSource.txt
//*******************************************************************
// This Module contains code derived from
// - OWBUS library example code
//*******************************************************************

//*******************************************************************
// OWBus Local Libraries
//*******************************************************************
// For ESP32-DevKitC PIN Configuration look at BeeIoT.h

#include <Arduino.h>
#include <stdio.h>
#include <esp_log.h>
#include "sdkconfig.h"
#include "FS.h"
#include "SD.h"

// DS18B20 libraries
#include <OneWire.h>
#include <DallasTemperature.h>

#include "beeiot.h"     // provides all GPIO PIN configurations of all sensor Ports !
#include "owbus.h"      // Provides OneWire bus device related settings

//***********************************************
// Global Sensor Data Objects
//***********************************************
// Setup a oneWire instance to communicate with a OneWire device
OneWire ds(ONE_WIRE_BUS);  // declare OneWire Bus Port with pullup

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature OWsensors(&ds);

DeviceAddress sensorInt = TEMP_0;   // Internal Temp. sensor
DeviceAddress sensorBH  = TEMP_1;   // BeeHive  Temp. sensor
DeviceAddress sensorExt = TEMP_2;   // External Temp. Sensor

extern dataset bhdb;                // central BeeIo DB
extern uint16_t	lflags;             // BeeIoT log flag field

void printAddress(DeviceAddress deviceAddress);

//*******************************************************************
// OW-bus Setup Routine
//*******************************************************************
int setup_owbus(int reentry) {
// put your setup code here, to run once:

// ONEWIRE Constructor
#ifdef ONEWIRE_CONFIG
  BHLOG(LOGOW) Serial.println("  OWBus: Init OneWire Bus");
  gpio_hold_dis(ONE_WIRE_BUS);
  OWsensors.begin();    // Init OW bus devices

    // locate devices on the bus
  BHLOG(LOGOW) Serial.print("  OWBus: searching OW devices...");
  BHLOG(LOGOW) Serial.print(OWsensors.getDS18Count(), DEC);
  BHLOG(LOGOW) Serial.print(" of ");
  BHLOG(LOGOW) Serial.print(OWsensors.getDeviceCount(), DEC);
  BHLOG(LOGOW) Serial.println(" devices found.");

 // show the addresses we found on the bus
  BHLOG(LOGOW) Serial.print("    Device 0: Int-Address: ");
	OWsensors.getAddress((uint8_t *)&sensorInt, 0);
  	printAddress(sensorInt);
  BHLOG(LOGOW) Serial.println();

  BHLOG(LOGOW) Serial.print("    Device 1: BH. Address: ");
	OWsensors.getAddress((uint8_t *)&sensorBH, 1);
  	printAddress(sensorBH);
  BHLOG(LOGOW) Serial.println();

  BHLOG(LOGOW) Serial.print("    Device 2: Ext.Address: ");
	OWsensors.getAddress((uint8_t *)&sensorExt, 2);
  	printAddress(sensorExt);
  BHLOG(LOGOW) Serial.println();


  BHLOG(LOGOW) Serial.print("  OWBus: Current Sensor Resolution: ");
  BHLOG(LOGOW) Serial.print(OWsensors.getResolution(sensorBH));
  BHLOG(LOGOW) Serial.println();

    // set the resolution to 12 bit per device
  OWsensors.setResolution(sensorInt, TEMPERATURE_PRECISION);
  OWsensors.setResolution(sensorBH,  TEMPERATURE_PRECISION);
  OWsensors.setResolution(sensorExt, TEMPERATURE_PRECISION);
  BHLOG(LOGOW) Serial.printf("  OWBUS: set sensor resolution: %i\n", OWsensors.getResolution(sensorBH));

#endif // ONEWIRE_CONFIG

  return 3;   // OneWire device port is initialized
} // end of setup_owbus()



// print DS Type string /wo new line depending on 1. Byte of DevAddr
int printDSType(byte DSType){
  // the first ROM byte indicates which chip
  int type_s=0;
  switch (DSType) { // analyse 1. Byte of devAddr
    case 0x10:
      BHLOG(LOGOW)   Serial.print(" DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      BHLOG(LOGOW) Serial.print(" DS18B20");
      type_s = 0;
      break;
    case 0x22:
      BHLOG(LOGOW) Serial.print(" DS1822");
      type_s = 0;
      break;
    default:
      BHLOG(LOGOW) Serial.print("No DS18x20 family device.");
      return(type_s);
  }
  return(type_s);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16)
      BHLOG(LOGOW) Serial.print("0");
    BHLOG(LOGOW) Serial.print(deviceAddress[i], HEX);
  }
  BHLOG(LOGOW) Serial.print(" ");
  printDSType(deviceAddress[0]);
}

// read One Wire Sensor data based on given IDs (owbus.h)
// Using Dallas temperature device library
// Input: INdex of Datarow entry in bhdb
// Return:  Number of read devices

void GetOWsensor(int sample){
#ifdef ONEWIRE_CONFIG
  BHLOG(LOGOW) Serial.println("  OWBus: Requesting temperatures...");
  OWsensors.requestTemperatures(); // Send the command to get temperatures (all at once)
  delay(500);

  bhdb.dlog[sample].TempIntern = OWsensors.getTempC(sensorInt);
  bhdb.dlog[sample].TempHive   = OWsensors.getTempC(sensorBH);
  bhdb.dlog[sample].TempExtern = OWsensors.getTempC(sensorExt);

  BHLOG(LOGOW) Serial.print("  OWBus: Int.Temp.Sensor (°C): ");
  BHLOG(LOGOW) Serial.println(bhdb.dlog[sample].TempIntern);

  BHLOG(LOGOW) Serial.print("  OWBus: Bee.Temp.Sensor (°C): ");
  BHLOG(LOGOW) Serial.println(bhdb.dlog[sample].TempHive);

  BHLOG(LOGOW) Serial.print("  OWBus: Ext.Temp.Sensor (°C): ");
  BHLOG(LOGOW) Serial.println(  bhdb.dlog[sample].TempExtern);

#endif // ONEWIRE_CONFIG
} // end of GetOWsensor()

// end of owbus.cpp