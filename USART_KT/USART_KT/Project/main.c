
/*****************************************************************************
  *Ten Tep          :     BlinkLED.c
  *Ngay             :     01/07/2017
  *Tac Gia          :     Do Huong
  *Phien Ban        :     V1.0
	*Noi dung         :     Turn on LED PB0 on Board STM32F103 
******************************************************************************/ 

/***************** Khai bao thu vien*******************************/
#include "main.h"
#include "user_delay.h"
#include "usart_config.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART2, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{
		//
	}

	return ch;
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

/***************** Khai bao cac ham********************************/
void GPIO_Configuration(void);

int main(void)
{
	/**************** Khai bao bien ngay sau ham main****************/
	//uint8_t nCount;
	uint16_t data_send = 12345; 
	uint16_t data_recv = 0;
	/**************** Khoi tao Clock cho he thong********************/	
	SystemInit();
	
	delay_init(72);
	
	USART2_Configuration(9600);
	//USART3_Configuration(9600);
	/**************** Write your code here***************************/
	while(1)
	{
		/*
		if(GetUSART(USART2) != 0)
		{
			printf("AT$0D$0A");
			delay_ms(2000);
			printf("\n");
		}
		*/
	}
}

void USART2_IRQHandler(void)
{
	uint16_t data;
    /* RXNE handler */
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        /* If received 't', toggle LED and transmit 'T' */
//        if((char)USART_ReceiveData(USART2) == 't')
//        {
//            USART_SendData(USART2, 'T');
//            /* Wait until Tx data register is empty, not really 
//             * required for this example but put in here anyway.
//             */
//            /*
//            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//            {
//            }*/
//        }
			if ((data = USART_ReceiveData(USART2)) != 0)
			{
				USART_SendData(USART2, data);
			}

    }
     
    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
}
 
