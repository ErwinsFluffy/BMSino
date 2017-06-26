#include "Arduino.h"
#include "current_sensor.h"

CURRENT_SENSOR my_CurrentSensor;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	my_CurrentSensor.begin(LEM_HAIS_50_P);
	pinMode(A5, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	delay(3000);
	/*
	Serial.print("La corrente è: ");
	Serial.println( getCurrent() );
	*/

	Serial.print("Hall_out: ");
	Serial.print( analogRead(HALL_SENSOR_OUT_PIN) );
	Serial.print("\tHall_ref: ");
	Serial.print( analogRead(HALL_SENSOR_REF_PIN) );
	Serial.print("\nCurrent is: ");
	Serial.println( my_CurrentSensor.getCurrent() );
	Serial.print("Raw Current Value is: ");
	Serial.println(my_CurrentSensor.getRawCurrentValue());

	digitalWrite(A5, LOW);
	delay(400);
	digitalWrite(A5,HIGH);
}
