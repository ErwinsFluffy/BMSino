/*
 * thermistor.cpp
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#include "thermistor.h"
#include <Arduino.h>

// thermistors Look-Up-Tables

#ifdef USE_NTC_LOWSIDE_B3950_5V_10Kohm
	//**************************************************************
	// MF58 by Cantherm 10kohm, B3950
	// http://www.cantherm.com/media/productPDF/cantherm_mf58_1.pdf
	//**************************************************************
	//							 |
	//						 ___/_
	//     +5V <--/\/\/--@--|__/__|---|| GND
	//                   |    /
	//		     10kohm  |   NTC 10k B3950
    //					 |
	//					Vout
	//
	//**************************************************************

#define MF58_LUT_SIZE 16
static const lut_t MF58[MF58_LUT_SIZE] ={
		{.ADC_value=	35	, .Temperature=		2009	},	    // 	125.56	°C
		{.ADC_value=	44	, .Temperature=		1859	},	    // 	116.2	°C
		{.ADC_value=	56	, .Temperature=		1707	},	    // 	106.71	°C
		{.ADC_value=	72	, .Temperature=		1555	},	    // 	97.17	°C
		{.ADC_value=	93	, .Temperature=		1404	},	    // 	87.76	°C
		{.ADC_value=	120	, .Temperature=		1258	},	    // 	78.62	°C
		{.ADC_value=	156	, .Temperature=		1110	},	    // 	69.37	°C
		{.ADC_value=	203	, .Temperature=		962		},	    // 	60.15	°C
		{.ADC_value=	263	, .Temperature=		816		},	    // 	51	°C
		{.ADC_value=	338	, .Temperature=		669		},	    // 	41.83	°C
		{.ADC_value=	427	, .Temperature=		524		},	    // 	32.74	°C
		{.ADC_value=	528	, .Temperature=		378		},	    // 	23.6	°C
		{.ADC_value=	634	, .Temperature=		231		},	    // 	14.45	°C
		{.ADC_value=	735	, .Temperature=		86		},	    // 	5.38	°C
		{.ADC_value=	824	, .Temperature=		-61		},	    // 	-3.79	°C
		{.ADC_value=	894	, .Temperature=		-206	},	    // 	-12.88	°C

};
#endif

#ifdef USE_NTC_LOWSIDE_B3977_5_2V_10Kohm
	//**************************************************************
	// Vishay NTCLE100E3103JB0
	// http://datasheet.octopart.com/NTCLE100E3103JB0-Vishay-Dale-datasheet-62311684.pdf
	//**************************************************************
	//							 			 |
	//						 			  ___/_
	//  AD7280 Vreg = +5.2V <--/\/\/--@--|__/__|---|| GND
	//         				          |    /
	//		     			  10kohm  |   NTC 10k B3977
    //					 			  |
	//						AD7280 AUXterm == NTC CHx
	//
	//**************************************************************

#define NTCLE100E3103JB0_LUT_SIZE 16
static const lut_t NTCLE100E3103JB0[NTCLE100E3103JB0_LUT_SIZE] ={
		{.ADC_value=	138		, .Temperature=		2004	},	    // 	125.24	°C
		{.ADC_value=	173		, .Temperature=		1857	},	    // 	116.08	°C
		{.ADC_value=	219		, .Temperature=		1710	},	    // 	106.87	°C
		{.ADC_value=	279		, .Temperature=		1564	},	    // 	97.74	°C
		{.ADC_value=	358		, .Temperature=		1418	},	    // 	88.62	°C
		{.ADC_value=	462		, .Temperature=		1273	},	    // 	79.53	°C
		{.ADC_value=	599		, .Temperature=		1127	},	    // 	70.45	°C
		{.ADC_value=	778		, .Temperature=		982		},	    // 	61.37	°C
		{.ADC_value=	1009	, .Temperature=		837		},	    // 	52.28	°C
		{.ADC_value=	1298	, .Temperature=		691		},	    // 	43.22	°C
		{.ADC_value=	1647	, .Temperature=		546		},	    // 	34.14	°C
		{.ADC_value=	2045	, .Temperature=		401		},	    // 	25.07	°C
		{.ADC_value=	2468	, .Temperature=		256		},	    // 	15.98	°C
		{.ADC_value=	2880	, .Temperature=		110		},	    // 	6.9		°C
		{.ADC_value=	3245	, .Temperature=		-35		},	    // 	-2.19	°C
		{.ADC_value=	3538	, .Temperature=		-180	},	    // 	-11.26	°C
};
#endif


int16_t THERMISTOR::interpolateLinearly(const lut_t* thermistorLUT_l, uint8_t LUTsize_l, uint16_t ADC_value_l){
	uint8_t i=0;
	while( i < LUTsize_l && ADC_value_l > thermistorLUT_l[i].ADC_value){	// find the nearest ADC_value (above the ADC_value_l) point in LUT -> ADC_value[i]
		i++;
	}
	if(i == LUTsize_l){ 	//make sure the point isn't past the end of the table
		return thermistorLUT_l[i-1].Temperature;
	}
	if( i == 0){			//make sure the point isn't before the beginning of the table
		return thermistorLUT_l[i].Temperature;
	}
#ifdef THERMISTOR_DEBUG
	Serial.print("i = ");
	Serial.println(i);
#endif
	// calculate the slope of the straight line between two points ( ADC_value[i-1] and ADC_value[i] )
	float m = (float)(thermistorLUT_l[i].Temperature - thermistorLUT_l[i-1].Temperature) /
				(float)(thermistorLUT_l[i].ADC_value - thermistorLUT_l[i-1].ADC_value);
	float q = (float)thermistorLUT_l[i-1].Temperature - m * (float)thermistorLUT_l[i-1].ADC_value;
#ifdef THERMISTOR_DEBUG
	Serial.print(thermistorLUT_l[i].Temperature);
	Serial.print("-");
	Serial.print(thermistorLUT_l[i-1].Temperature);
	Serial.print("\\");
	Serial.print(thermistorLUT_l[i].ADC_value);
	Serial.print("-");
	Serial.print(thermistorLUT_l[i-1].ADC_value);
	Serial.print("m = ");
	Serial.println(m);
	Serial.print("q = ");
	Serial.println(q);
#endif
	//this is the solution to the point slope formula
	return (m * ADC_value_l + q);	// y = m * x + q
}

THERMISTOR::THERMISTOR(){
}

boolean THERMISTOR::begin(thermistorType_t thermistorType_l){
		thermistorType = thermistorType_l;
		return true;
}

int16_t THERMISTOR::getTemperatureFromADCValue(uint8_t ADCpin_l){
	uint16_t ADC_sample;
	int16_t temp;
	ADC_sample = analogRead(ADCpin_l);
	temp = interpolateLinearly(MF58, MF58_LUT_SIZE, ADC_sample);
	return  temp;
};

