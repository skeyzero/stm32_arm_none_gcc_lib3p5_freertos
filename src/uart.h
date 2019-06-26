#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

/**********************************************************************
		UART function definition
***********************************************************************/


#define BAUDRATE9600		0
#define BAUDRATE115200		1
#define BAUDRATE19200		2

#define Rx1_Buf_Length 	250		/*definiction of receive buff length*/
#define Rx2_Buf_Length 	250
#define Rx3_Buf_Length	250
#define Rx4_Buf_Length 	250
#define Rx5_Buf_Length	250

void UART1_Init(u32 bound);
void UART1_Send(u8 tx_data);

void UART2_Init(u32 bound);
void UART2_Send(u8 tx_data);

void UART3_Init(u32 bound);
void UART3_Send(u8 tx_data);

void UART4_Init(u32 bound);
void UART4_Send(u8 tx_data);

void UART5_Init(u32 baud_rate);
void UART5_Send(u8 tx_data);

void UART5_SendString(u8* str);
#endif

