/*
 * thermistor.h
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <stdint.h>

// type of thermistor
typedef enum{
	NTC,
	PTC,	// not yet implemented
}thermistorType_t;

// class THERMISTOR
class THERMISTOR{
	public:
		THERMISTOR();
		bool begin(thermistorType_t thermistorType, float Vref, uint32_t seriesResistance,uint16_t Beta,uint32_t R0, uint32_t T0);
		float getTemperatureFromVoltage(uint16_t measuredVoltage);
	private:

		thermistorType_t thermistorType;
		float Vref;
		uint32_t seriesResistance;
		uint16_t Beta;
		uint32_t R0;
		uint32_t T0;

		uint32_t getResistanceFromVoltage(uint16_t measuredVoltage);
};


#endif /* THERMISTOR_H */
