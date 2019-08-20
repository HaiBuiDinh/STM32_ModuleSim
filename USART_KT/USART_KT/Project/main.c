#include "main.h"
#include "user_delay.h"
#include "usart_config.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

//PUTCHAR_PROTOTYPE
//{
//	/* Place your implementation of fputc here */
//	/* e.g. write a character to the USART */
//	USART_SendData(USART2, (uint8_t) ch);

//	/* Loop until the end of transmission */
//	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
//	{
//		//
//	}

//	return ch;
//}

void GPIO_Configuration(void);

int main(void)
{
	SystemInit();
	
	delay_init(72);
	
	//enable usart1 and 2
	USART1_Configuration(9600);
	USART2_Configuration(9600);
	
	while(1)
	{
		
	}
}



void Init_GPIO(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
	
	GPIO_Structure.GPIO_Pin =  GPIO_Pin;
	GPIO_Structure.GPIO_Mode=  GPIO_Mode;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOx, &GPIO_Structure);
	
	GPIO_SetBits(GPIOx, GPIO_Pin);
}

 
