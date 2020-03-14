#include "DAC.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"
#include "main.h"

uint8_t upperByte,lowerByte; // temporary buffer for MOSI Data
uint8_t tx_data[2]; 		 // Array for SPI HAL to transmitt

DAC::DAC()
{

}

DAC::~DAC()
{

}

void DAC::init(SPI_HandleTypeDef* SPIx,GPIO_TypeDef* CSn_Port, uint16_t CSn_Pin)
{
	SPI = SPIx;
	CS_Port = CSn_Port;
	CS_Pin = CSn_Pin;
}


void DAC::set_Channel_A(uint16_t output)
{
	upperByte = (output >> 8) | 0x30; 					// Set DAC A, no Buffering,no Shutdown
	lowerByte = output & 0xFF; 							// Keep only lower 8 bit
	upperByte &= ~(1 << 7);  						    // Set Channel A
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET);   // Start Transmission
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
	output_register[0] = output;
}

void DAC::set_Channel_B(uint16_t output)
{

	upperByte = (output >> 8) | 0x30; 				// Set DAC A, no Buffering,no Shutdown
	lowerByte = output & 0xFF;		  				// Keep only lower 8 bit
	upperByte |= (1 << 7);  						// Set Channel B
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET); //Start Transmission
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
	output_register[1] = output;
}

void DAC::set_buffer(bool enable)
{
	upperByte = (output_register[0] >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	lowerByte = output_register[0] & 0xFF;
	upperByte |= (enable << 14);  				  // Write Buffer Bit
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
}


void DAC::set_gain(uint8_t gain)
{
	upperByte = (output_register[0] >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	lowerByte = output_register[0] & 0xFF;
	upperByte |= (gain << 13);  				  // Write Gain Bit
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
}

void DAC::shutdown_dac(void)
{
	upperByte = (output_register[0] >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	lowerByte = output_register[0] & 0xFF;
	upperByte |= (1 << 12);  					  // Write ~SHTDN Bit -> Put DAC in Sleep
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
}

void DAC::enable_dac(void)
{
	upperByte = (output_register[0] >> 8) | 0x30; // Set DAC A, no Buffering,no Shutdown
	lowerByte = output_register[0] & 0xFF;
	upperByte &=~ (1 << 12);  					  // Write ~SHTDN Bit HIGH -> Wake Up DAC
	tx_data[0] = upperByte;
	tx_data[1] = lowerByte;
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPI,tx_data,2,1);
	HAL_GPIO_WritePin(CS_Port,CS_Pin,GPIO_PIN_SET);
}

void DAC::get_dac_voltages(uint16_t* voltages)
{
	voltages [0] =output_register[0];
	voltages [1] = output_register[1];
}
