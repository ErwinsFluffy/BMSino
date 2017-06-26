/*
 * current_sensor.cpp
 *
 *  Created on: 23 Mar 2017
 *      Author: Erwin's Fluffy
 */

#include "current_sensor.h"
#include <Arduino.h>

#define Vresolution_mV	0.00489

//	define Current Transducer details

//	model: LEM HAIS 50-P (HALL effect sensor)
// 	datasheet: http://www.lem.com/docs/products/hais_50_400-p_and_50_150-tp.pdf
#define I_PN 	50.0	// primary nominal current RMS
#define I_MAX 	150.0	// not used
#define G_TH	0.625	// theoretical sensitivity

//	model: INA170 (High-Side, Bidirectional CURRENT SHUNT MONITOR)
// 	datasheet: www.ti.com/lit/ds/sbos193d/sbos193d.pdf
#define Rsense 0.22		// value of sense resistor in ohm
#define Vref	2.5		// value of the reference voltage, in volt

bool CURRENT_SENSOR::begin(currentsensorType_t currentsensorType_l){
		if(currentsensorType_l == LEM_HAIS_50_P){
			scale_factor = Vresolution_mV * I_PN / G_TH;
		}
		else if(currentsensorType_l == INA170_CSA){
			scale_factor = Vresolution_mV / Rsense;
		}
		else if(currentsensorType_l == EXTERNAL_HALL_EFFECT){
			scale_factor = 1;
		}
		else
			return false;
}

CURRENT_SENSOR::CURRENT_SENSOR(){
}

float CURRENT_SENSOR::getCurrent(){
	uint16_t hall_sensor_out;
	uint16_t hall_sensor_ref;
	hall_sensor_out = analogRead(HALL_SENSOR_OUT_PIN);
	hall_sensor_ref = analogRead(HALL_SENSOR_REF_PIN);
	return (((float)hall_sensor_out - (float)hall_sensor_ref) * scale_factor);
}

int16_t CURRENT_SENSOR::getRawCurrentValue(){
	return (analogRead(HALL_SENSOR_OUT_PIN)-analogRead(HALL_SENSOR_REF_PIN));
}
