#include "Arduino.h"
#include "BMSino.h"
#include "debug_f\scope.h"

BMSino myBMS;
uint8_t activity_led_status;

void setup()
{
	Serial.begin(9600);
	myBMS.begin();
}


void loop()
{
	delay(1000);
	/*	read BMS temperature 	*/
	Serial.print("OnBoardNTC value is : ");
	Serial.println((float)myBMS.OnBoardNTC.getTemperature()/16);
	/*	read battery current 	*/
	Serial.print("Current sensor read value is : ");
	Serial.println((float)myBMS.Lem_Hais_50P.getCurrent());
	/*	blink activity led	*/
	activity_led_status ^= 1;
	digitalWrite(ACTIVITY_LED_PIN, activity_led_status);

}
