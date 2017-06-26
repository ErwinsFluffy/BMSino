#include "Arduino.h"
#include "thermistor.h"

#define NTC_PIN A4

THERMISTOR my_ntc;
bool i=true;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	my_ntc.begin(ONBOARD_NTC, A4);
	Serial.begin(9600);
	pinMode(A4,INPUT);
	pinMode(A5, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	delay(1000);
	Serial.print("Actual temperature is: ");
	Serial.println( my_ntc.getTemperature() / 16.0 );
	Serial.print("Actual ADC value is: ");
	Serial.println(analogRead(A4)*0.00489);

	i^=1;
	digitalWrite(A5, i);
}
