/******************************************************************************
arduino_mpu9250_i2c.cpp - MPU-9250 Digital Motion Processor Arduino Library 
Jim Lindblom @ SparkFun Electronics
original creation date: November 23, 2016
https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

This library implements motion processing functions of Invensense's MPU-9250.
It is based on their Emedded MotionDriver 6.12 library.
	https://www.invensense.com/developers/software-downloads/

Development environment specifics:
Arduino IDE 1.6.12
SparkFun 9DoF Razor IMU M0

Supported Platforms:
- ATSAMD21 (Arduino Zero, SparkFun SAMD21 Breakouts)
******************************************************************************/
#include "arduino_mpu9250_i2c.h"
#include <Arduino.h>
#include <Wire.h>

extern TwoWire Wire;
extern TwoWire muxWire;
TwoWire *w = &Wire;


void arduino_i2c_set(int select)
{
    if (select == 0) {
        w = &Wire;
    } else {
        w = &muxWire;
    }
}

int arduino_i2c_write(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
	w->beginTransmission(slave_addr);
	w->write(reg_addr);
	for (unsigned char i = 0; i < length; i++)
	{
		w->write(data[i]);
	}
	w->endTransmission(true);
	
	return 0;
}

int arduino_i2c_read(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
	w->beginTransmission(slave_addr);
	w->write(reg_addr);
	w->endTransmission(false);
	w->requestFrom(slave_addr, length);
	for (unsigned char i = 0; i < length; i++)
	{
		data[i] = w->read();
	}
	
	return 0;
}
