#include "usart_config.h"

//Hàm doc data USART
uint8_t GetUSART(USART_TypeDef* USARTx)
{
	while (USART_GetFlagStatus(USARTx, USART_IT_RXNE) == RESET)	{	}
	return USART_ReceiveData(USARTx);
}

/* Config USART3 */
void USART1_Configuration(uint32_t Baudrate)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	/* Enable USART3 Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	/* Configure USART3 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART3 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* Configure USART3 */
	USART_Init(USART1, &USART_InitStructure);
	/* xoa co ngat nhan cho lan dau su dung*/
	USART_ClearFlag(USART1, USART_IT_RXNE);
	
	/* Cau hinh cho phep ngat nhan*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* Cho phep UART hoat dong */
	USART_Cmd(USART1, ENABLE);
	
	/* Cau hinh vector ngat va muc uu tien */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART2_Configuration(uint32_t Baudrate)
{
		// Initialization struct
	USART_InitTypeDef UART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/*Cap clock cho USART và port su dung*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Cau Tx mode AF_PP, Rx mode FLOATING  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*Cau hinh USART*/
	UART_InitStructure.USART_BaudRate = Baudrate;
	UART_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART_InitStructure.USART_StopBits = USART_StopBits_1;
	UART_InitStructure.USART_Parity = USART_Parity_No;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &UART_InitStructure);
		
/* Cau hinh vector ngat va muc uu tien */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* xoa co ngat nhan cho lan dau su dung*/
	USART_ClearFlag(USART2, USART_IT_RXNE);
	
	/* Cau hinh cho phep ngat nhan*/
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Cho phep UART hoat dong */
	USART_Cmd(USART2, ENABLE);
}

void U_PutChar( USART_TypeDef* USARTx, char c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
	// Send a char using USART2
	USART_SendData(USARTx, c);
}

void U_putString(USART_TypeDef* USARTx, char *s)
{
	while (*s)
	{
		U_PutChar(USARTx, *s++);
	}
}
