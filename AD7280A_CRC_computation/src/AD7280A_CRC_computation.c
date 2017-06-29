/*
 ============================================================================
 Name        : AD7280A_CRC_computation.c
 Author      : Luca Buccolini
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================

 /******************************************************************************************
 * Be careful when use scanf(): console will not update until the program ends.
 * The BUG no. 173732 of Eclipse CDT console is described here:
 * https://bugs.eclipse.org/bugs/show_bug.cgi?id=173732#c2
 *
 * WORKAROUND: use fflush(stdout) after each printf() instruction.
 *
 ******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int8_t i=0;
uint8_t NumBits = 0;
uint8_t xor_0=0, xor_1=0, xor_2=0, xor_3=0, xor_5=0;
uint32_t data_in; //21 bit for a data write to the AD7280A, and 22 bit for a data read from the AD7280A.
uint8_t CRC_0=0, CRC_1=0, CRC_2=0, CRC_3=0, CRC_4=0, CRC_5=0, CRC_6=0, CRC_7=0;
uint32_t CRC_TOT;
char input_string[2];


int main(void) {

	printf("Premi w se il comando è di scrittura, r se il comando è di lettura, poi premi invio\n");
	fflush(stdout);
	scanf("%s",input_string);
	if(strcmp(input_string, "w") == 0){
		NumBits = 21;
		printf("NumBits=%d\n", NumBits);
		fflush(stdout);
	}
	else if (strcmp(input_string, "r") == 0){
		NumBits = 22;
		printf("NumBits=%d\n", NumBits);
		fflush(stdout);
	}
	else{
		printf("inserisci la lettera corretta!");
		return 0;
	}


	printf("Inserisci il valore data_in di cui vuoi calcolare il CRC e premi invio\n");
	fflush(stdout);
	scanf("%x",&data_in);
	printf("il valore ricevuto è: 0X%X\n", data_in);
	fflush(stdout);

	for((i=NumBits-1); i>=0; i--){
		xor_5 = CRC_4 ^ CRC_7 ;
		xor_3 = CRC_2 ^ CRC_7 ;
		xor_2 = CRC_1 ^ CRC_7 ;
		xor_1 = CRC_0 ^ CRC_7 ;
		xor_0 = ((data_in >> i) & 1) ^ CRC_7;

		CRC_7 = CRC_6;
		CRC_6 = CRC_5;
		CRC_5 = xor_5;
		CRC_4 = CRC_3;
		CRC_3 = xor_3;
		CRC_2 = xor_2;
		CRC_1 = xor_1;
		CRC_0 = xor_0;
	}
/*
	printf("il CRC_0 calcolato è: %x\n", CRC_0);
	fflush(stdout);
	printf("il CRC_1 calcolato è: %x\n", CRC_1);
	fflush(stdout);
	printf("il CRC_2 calcolato è: %x\n", CRC_2);
	fflush(stdout);
	printf("il CRC_3 calcolato è: %x\n", CRC_3);
	fflush(stdout);
	printf("il CRC_4 calcolato è: %x\n", CRC_4);
	fflush(stdout);
	printf("il CRC_5 calcolato è: %x\n", CRC_5);
	fflush(stdout);
	printf("il CRC_6 calcolato è: %x\n", CRC_6);
	fflush(stdout);
	printf("il CRC_7 calcolato è: %x\n", CRC_7);
	fflush(stdout);
*/
	CRC_TOT = CRC_7<<7 | CRC_6<<6 | CRC_5<<5 | CRC_4<<4 | CRC_3<<3 | CRC_2<<2 | CRC_1<<1 | CRC_0;

	uint32_t DataToSend = ((data_in << 11) | (CRC_TOT << 3) | 0b10);


	// Swap endian (big to little) or (little to big)
	uint32_t b0,b1,b2,b3;

	b0 = (DataToSend & 0x000000ff) << 24u;
	b1 = (DataToSend & 0x0000ff00) << 8u;
	b2 = (DataToSend & 0x00ff0000) >> 8u;
	b3 = (DataToSend & 0xff000000) >> 24u;

	uint32_t res = b0 | b1 | b2 | b3;

	printf("CRC_TOT value is 0x%X\n", CRC_TOT);
	printf("Data to send to the AD7280A is: 0x%X\n", DataToSend);

	printf("Data to send (swapped) to the AD7280A is: 0x%X\n", res);

	return 0;
}
