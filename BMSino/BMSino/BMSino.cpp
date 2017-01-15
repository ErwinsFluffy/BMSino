/*
 * BMSino.cpp
 *
 *  Created on: 31 Dec 2016
 *      Author: Erwin's Fluffy
 */

#include "BMSino.h"
#include <Arduino.h>

void BMSino::begin(){
	pinMode(ACTIVITY_LED, OUTPUT);
	pinMode(AD7280_CNVST, OUTPUT);
	//pinMode(DIN_1, INPUT);
	pinMode(AD7280_ALERT, INPUT);
	pinMode(EXT_SPI_CS, OUTPUT);
	pinMode(AD7280_PD, OUTPUT);
	pinMode(LSOUT_1, OUTPUT);
	pinMode(DCDC_EN, OUTPUT);
	pinMode(DIN_2, INPUT);
	pinMode(LSOUT_2, OUTPUT);
	pinMode(AD7280_CS, OUTPUT);
	pinMode(SPI_MOSI, OUTPUT);
	pinMode(SPI_MISO, INPUT);
	pinMode(SPI_SCK, OUTPUT);
	pinMode(I2C_SDA, OUTPUT);
	pinMode(I2C_SCL, OUTPUT);
}



