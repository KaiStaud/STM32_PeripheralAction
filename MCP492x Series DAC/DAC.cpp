#include "DAC.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"

DAC::DAC()
{

}

DAC::DAC(SPI_HandleTypeDef SPIx, GPIO_TypeDef CSn_Port, uint16_t CSn_Pin)
{
	SPI = SPIx;
	CS_Port = CSn_Port;
	CS_Pin = CSn_Pin;
}


void DAC::set_Channel_A(uint16_t output)
{
	uint8_t tx_data[2];
	uint8_t upperByte = (output >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	uint8_t lowerByte = output & 0xFF;// Keep only lower 8 bit
	upperByte &= ~(1 << 7); // Enable DAC A
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(&CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI,tx_data,2,1);
	HAL_GPIO_WritePin(&CS_Port,CS_Pin,GPIO_PIN_SET);
	output_register[0] = output;
}

void DAC::set_Channel_B(uint16_t output)
{
	uint8_t tx_data[2];
	uint8_t upperByte = (output >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	uint8_t lowerByte = output & 0xFF;// Keep only lower 8 bit
	upperByte &= (1 << 7); // Enable DAC B
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(&CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI,tx_data,2,1);
	output_register[1] = output;
}

void DAC::set_buffer(bool enable)
{

}

void DAC::set_gain(uint8_t gain)
{

}

void DAC::shutdown_dac(void)
{

}

void DAC::enable_dac(void)
{

}

void DAC::get_dac_voltages(uint16_t* voltages)
{

}
