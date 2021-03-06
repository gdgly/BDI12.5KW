
/*
 * AD5328_app.c
 *
 *  Created on: Feb 14, 2014
 *      Author: Hanif
 */

#include "external/AD5328_app.h"

void AD5328_Init(void)
{
	//Set output Serial clock SCLK_DAC P3.0
	WR_REG(DATA_PORT->IOCR0,PORT3_IOCR0_PC0_Msk,PORT3_IOCR0_PC0_Pos,0x10);
	CLR_BIT(DATA_PORT->OUT,SCLK);
	//Set output Serial data MOSI_DAC P3.11
	WR_REG(DATA_PORT->IOCR8,PORT3_IOCR8_PC11_Msk,PORT3_IOCR8_PC11_Pos,0x10);
	CLR_BIT(DATA_PORT->OUT,MOSI);
	//Set output Chip select SS_DAC P3.1
	WR_REG(DATA_PORT->IOCR0,PORT3_IOCR0_PC1_Msk,PORT3_IOCR0_PC1_Pos,0x10);
	SET_BIT(DATA_PORT->OUT,CS);
	//Set output DAC Update LDAC P3.12
	WR_REG(DATA_PORT->IOCR12,PORT3_IOCR12_PC12_Msk,PORT3_IOCR12_PC12_Pos,0x10);
	SET_BIT(DATA_PORT->OUT,LDAC);
}

void AD5328_Send_Data(int32_t dac,int32_t data)
{
	//dac --> value from 0 to 7
	//data --> value from 0 to 4095
	//clock 100KHz
	int8_t count=0;
	int8_t bit=0;
	if(dac>7)
	{
		dac=7;
	}

	WR_REG(data,0x01UL<<15,15,0);
	WR_REG(data,0x07UL<<12,12,dac);

	//Initialization
	SCLK_LOW();
	CS_HIGH();

	//Send some clock while CS_HIGH
	TOGGLE_SCLK();
	My_Delay_us(CLOCK);
	TOGGLE_SCLK();
	My_Delay_us(CLOCK);

	TOGGLE_SCLK();
	My_Delay_us(CLOCK);
	TOGGLE_SCLK();
	My_Delay_us(CLOCK);

	TOGGLE_SCLK();
	My_Delay_us(CLOCK);
	TOGGLE_SCLK();
	My_Delay_us(CLOCK);

	//Start sending data
	CS_LOW();

	for(bit=0;bit<16;bit++)
	{
		WRITE_MOSI(data & 0x00008000);
		TOGGLE_SCLK();
		My_Delay_us(CLOCK);
		TOGGLE_SCLK();
		data<<=1;
		My_Delay_us(CLOCK);
	}

	//Update value to dac
	LDAC_LOW();
	My_Delay_us(1);
	LDAC_HIGH();

	//finish
}

void AD5328_Set_Value_Volt(int32_t dac,float volt)
{
	int32_t data;

	if(volt>ADREF)
	{volt = ADREF;}

	data = (int32_t)(volt/ADREF*4095.0f);
	AD5328_Send_Data(dac, data);
}
