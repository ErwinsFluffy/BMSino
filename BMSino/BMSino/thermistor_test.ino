#include "Arduino.h"
#include "thermistor.h"

#define NTC_PIN A0

THERMISTOR my_ntc;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	my_ntc.begin(TEST_NTC, NTC_PIN);
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	delay(1000);

	Serial.print("La temperatura è: ");
	Serial.println( my_ntc.getTemperature() / 16.0 );
}
