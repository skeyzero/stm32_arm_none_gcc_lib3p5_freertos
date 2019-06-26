#include "uart.h"

#include "hw.h"


void UART1_Init(u32 bound)
{
	RCC->APB2ENR |= 1 << 2;//Enable PA clock
	
	
	GPIOA->CRH &= 0xfffff00f;//清除PA9,PA10设置位
	GPIOA->CRH |= 0x000008b0;//PA9 复用推皖输出，PA10浮空输入
	RCC->APB2ENR|=1<<14; //串口使能

    RCC->APB2RSTR|=1<<14;	//复位串口
    RCC->APB2RSTR&=~(1<<14);//
	
    USART1->BRR=0x0271;//设置波特率
    USART1->CR1|=0x202c;//设置停止位
	
	NVIC_Set(2,0,0x25,2);//设置串口中断
}

void UART2_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 2;//Enable PA clock
	
	GPIOA->CRL &= 0xffff00ff;//清除PA2,PA3设置位
	GPIOA->CRL |= 0x00004b00;//PA2复用推皖输出,PA3浮空输入
	
	RCC->APB1ENR|=1<<17; //串口使能

    RCC->APB1RSTR|=1<<17;	//复位串口
    RCC->APB1RSTR&=~(1<<17);//
	
    USART2->BRR=0x0138;//设置波特率
    USART2->CR1|=0x202c;//设置停止位,设置接受中断使能
	
	NVIC_Set(2,1,0x26,2);//设置串口中断
}

/*
PC10		TX
PC11		RX
*/
void UART4_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 4;//Enable PC clock
	GPIOC->CRH &= 0xffff00ff;//清除PC10,PC11设置位
	GPIOC->CRH |= 0x00004b00;//PC10 复用推皖输出，PC11浮空输入
	RCC->APB1ENR|=1<<19; //串口使能
    RCC->APB1RSTR|=1<<19;	//复位串口
    RCC->APB1RSTR&=~(1<<19);//
	switch(baud_rate)
	{
		case BAUDRATE9600: UART4->BRR=0x0EA;break;
		case BAUDRATE115200: UART4->BRR=0x0138;break;
		default:
			 UART4->BRR=0x0138;break;//其它波特率设置为
	}
    UART4->CR1|=0x202c;//设置停止位,设置接受中断使能
	NVIC_Set(2,1,52,2);//设置串口中断
}

/*
PC12	TX
PD2		RX
*/
void UART5_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 4;			//Enable PC clock
	RCC->APB2ENR |= 1 << 5;			//Enable PD clock
	
	GPIOC->CRH &= 0xfff0ffff;		//PC12 IO配置
	GPIOC->CRH |= 0x000b0000;		
	
	GPIOD->CRL &= 0xfffff0ff;		//PD2  IO配置
	GPIOD->CRL |= 0x00000400;
	
	RCC->APB1ENR	|= 1<<20; 		//串口时钟使能
	
    RCC->APB1RSTR	|= 1<<20;		//复位串口
    RCC->APB1RSTR	&= ~(1<<20);	
	
	switch(baud_rate)
	{
		case BAUDRATE9600: UART5->BRR=0x0EA;break;
		case BAUDRATE19200:	 UART5->BRR=0x753;break;
		case BAUDRATE115200: UART5->BRR=0x0138;break;
		default:
			 UART5->BRR=0x0138;break;//其它波特率设置为
	}
    UART5->CR1|=0x202c;//设置停止位,设置接受中断使能
	NVIC_Set(2,1,53,0);//设置串口中断
}




void UART1_Send(u8 tx_data)
{
	while((USART1->SR & (0x40)) == 0){}//判断发送缓冲区为空
	 USART1->DR = tx_data;
}

void UART2_Send(u8 tx_data)
{
	while((USART2->SR & (0x40)) == 0){}//判断发送缓冲区为空
	USART2->DR = tx_data;
}

void UART4_Send(u8 tx_data)
{
	while((UART4->SR & (0x40)) == 0);//等待发送完毕
	UART4->DR = tx_data;
}

void UART5_Send(u8 tx_data)
{
	while((UART5->SR & (0x40)) == 0);//等待发送完毕
	UART5->DR = tx_data;
}


void UART5_SendString(u8* str)
{
    while(*str != '\0')
    {
        UART5_Send(*str);
        str ++;
    }
}
