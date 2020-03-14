#pragma once
#include "inttypes.h"
#include "stm32f4xx_hal.h"

class DAC
{
private:
	SPI_HandleTypeDef* SPI;
	GPIO_TypeDef* CS_Port;
	uint16_t CS_Pin;
	uint16_t output_register[2];
	bool buffer_state;
	bool internal_gain;
	bool output_power_down;

protected:

public:
	DAC();
	virtual ~DAC();
	void init(SPI_HandleTypeDef* SPIx,GPIO_TypeDef* CSn_GPIO_Port,uint16_t CSn_Pin);//, GPIO_TypeDef* CSn_Port, uint16_t CSn_Pin);
	void set_Channel_A(uint16_t output);
	void set_Channel_B(uint16_t output);
	void set_buffer(bool enable);
	void set_gain(uint8_t gain);
	void shutdown_dac(void);
	void enable_dac(void);
	void get_dac_voltages(uint16_t* voltages);
};

