/*
 * thermistor.h
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#ifndef THERMISTOR_H
#define THERMISTOR_H
/*
	see here:
	https://stratifylabs.co/embedded%20design%20tips/2013/10/03/Tips-ADC-Thermistor-Circuit-and-Lookup-Table/
*/

#include <stdint.h>

#define THERMISTOR_DEBUG
#define USE_NTC_LOWSIDE_B3950_5V_10Kohm		// select the NTC to enable
#define USE_NTC_LOWSIDE_B3977_5_2V_10Kohm


// TYPES
typedef struct{
	uint16_t 	ADC_value;		// value read back from the 10bit-ADC
	int16_t		Temperature;	// expressed as 1/16 °C
}lut_t;

// type of thermistor
typedef enum: uint8_t {
	NTC_LOWSIDE_B3950_5V_10Kohm,	// thermistor in low side connected to Vcc = 5V and series resistor = 10k
	NTC_LOWSIDE_B3977_5_2V_10Kohm,
	OTHER 							// not yet implemented
}thermistorType_t;

// class THERMISTOR
class THERMISTOR{
	public:
		THERMISTOR();
		bool begin(thermistorType_t thermistorType_l);
		int16_t getTemperatureFromADCValue(uint8_t ADCpin);
	private:
		thermistorType_t thermistorType;
		int16_t interpolateLinearly(const lut_t* thermistorLUT_l, uint8_t LUTsize_l, uint16_t ADC_value_l);
};

#endif /* THERMISTOR_H */
