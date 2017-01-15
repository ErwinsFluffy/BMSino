/*
 * BMSino.h
 *
 *  Created on: 31 Dec 2016
 *      Author: Erwin's Fluffy
 */

#ifndef BMSINO_H
#define BMSINO_H

#define ACTIVITY_LED			A5
#define	TEMPERATURE_SENSOR		A4
#define AIN_2					A3
#define AIN_1					A2
#define CURR_S_OUT				A1
#define CURR_S_REF				A0

#define AD7280_CNVST			2
#define DIN_1					2
#define AD7280_ALERT			3
#define	EXT_SPI_CS				4
#define	AD7280_PD				5
#define LSOUT_1					6
#define DCDC_EN					7
#define	DIN_2					8
#define	LSOUT_2					9
#define	AD7280_CS				10

#define	SPI_MOSI				11
#define SPI_MISO				12
#define SPI_SCK					13

#define	I2C_SDA					SDA
#define	I2C_SCL					SCL


class BMSino{
	public:
		BMSino();
		void begin();

	private:

};

#endif /* BMSINO_H */
