
#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>

#include "BMSino.h"
#include "debug_f\scope.h"



BMSino myBMS;
uint8_t activity_led_status;
uint32_t SPI_buffer;


void setup()
{
	Serial.begin(9600);
	myBMS.begin();

	/* The following part of code must be a part of the AD7280A module. External libraries inclusion issue (i.e. SPI library) must be solved first! */
	//------------------------------- begin of code that should be a part of 7280A.c module----------------------------
	SPI.begin();
	// The register address, data bits, and CRC bits of AD8270A are input MSB first.
	// The AD7280A serial interface is Mode 1 SPI compliant.
	SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1));
	delay(100);

	//To select the self-test conversion, set Bits[D15:D14] of the control register 0 to 1, and set Bits[D13:D12] of the control register to 0 on all parts
	digitalWrite(AD7280_CS_PIN, LOW);
	//SPI_buffer = 0x1B80082;
	SPI_buffer = 0x8200B801;	// check endianness
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);

	delayMicroseconds(5);

	// Set Bits of the control register 1
	digitalWrite(AD7280_CS_PIN, LOW);
	//SPI_buffer = 0x70C56A;
	SPI_buffer = 0x6AC57000;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	//------------------------------- end of code that should be a part of 7280A.c module----------------------------

}


void loop()
{
	delay(1000);
	//	read BMS temperature
	Serial.print("OnBoardNTC value is : ");
	Serial.println((float)myBMS.OnBoardNTC.getTemperature()/16);
	//	read battery current
	Serial.print("Current sensor read value is : ");
	Serial.println((float)myBMS.Lem_Hais_50P.getCurrent());
	//	blink activity led
	activity_led_status ^= 1;
	digitalWrite(ACTIVITY_LED_PIN, activity_led_status);

}

