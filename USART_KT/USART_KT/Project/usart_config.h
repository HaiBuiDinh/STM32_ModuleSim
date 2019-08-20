#ifndef __USART_CONFIG_H
#define __USART_CONFIG_H

	#include "stm32f10x.h"

	uint8_t GetUSART(USART_TypeDef* USARTx);
	void USART1_Configuration(uint32_t Baudrate);
	void USART2_Configuration(uint32_t Baudrate);
	void U_putString(USART_TypeDef* USARTx, char *s);

#endif
