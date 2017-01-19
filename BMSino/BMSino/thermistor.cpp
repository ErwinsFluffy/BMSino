/*
 * thermistor.cpp
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#include "thermistor.h"
#include <Arduino.h>
#include <math.h>

THERMISTOR::THERMISTOR(){
}

boolean THERMISTOR::begin(thermistorType_t thermistorType_l, float Vref_l, uint32_t seriesResistance_l,uint16_t Beta_l, uint32_t R0_l, uint32_t T0_l){
		thermistorType = thermistorType_l;
		Vref = Vref_l;
		seriesResistance = seriesResistance_l;
		Beta = Beta_l;
		R0 = R0_l;
		T0 = T0_l;
		return true;
}

float THERMISTOR::getTemperatureFromVoltage(uint16_t measuredVoltage){
	float ret;
	ret = log(getResistanceFromVoltage(measuredVoltage) / R0);	// ln(R/R0)
	ret /= Beta;												// 1/B * ln(R/R0)
	ret += (1/T0);												// 1/T0 + 1/B * ln(R/R0)
	ret = 1/ret;												// invert
	return ret;
};

uint32_t THERMISTOR::getResistanceFromVoltage(uint16_t measuredVoltage){
	return ( measuredVoltage * seriesResistance ) / ( Vref - measuredVoltage ) ;
};
