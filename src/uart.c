#include "uart.h"

#include "hw.h"


void UART1_Init(u32 bound)
{
	RCC->APB2ENR |= 1 << 2;//Enable PA clock
	
	
	GPIOA->CRH &= 0xfffff00f;//���PA9,PA10����λ
	GPIOA->CRH |= 0x000008b0;//PA9 �������������PA10��������
	RCC->APB2ENR|=1<<14; //����ʹ��

    RCC->APB2RSTR|=1<<14;	//��λ����
    RCC->APB2RSTR&=~(1<<14);//
	
    USART1->BRR=0x0271;//���ò�����
    USART1->CR1|=0x202c;//����ֹͣλ
	
	NVIC_Set(2,0,0x25,2);//���ô����ж�
}

void UART2_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 2;//Enable PA clock
	
	GPIOA->CRL &= 0xffff00ff;//���PA2,PA3����λ
	GPIOA->CRL |= 0x00004b00;//PA2�����������,PA3��������
	
	RCC->APB1ENR|=1<<17; //����ʹ��

    RCC->APB1RSTR|=1<<17;	//��λ����
    RCC->APB1RSTR&=~(1<<17);//
	
    USART2->BRR=0x0138;//���ò�����
    USART2->CR1|=0x202c;//����ֹͣλ,���ý����ж�ʹ��
	
	NVIC_Set(2,1,0x26,2);//���ô����ж�
}

/*
PC10		TX
PC11		RX
*/
void UART4_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 4;//Enable PC clock
	GPIOC->CRH &= 0xffff00ff;//���PC10,PC11����λ
	GPIOC->CRH |= 0x00004b00;//PC10 �������������PC11��������
	RCC->APB1ENR|=1<<19; //����ʹ��
    RCC->APB1RSTR|=1<<19;	//��λ����
    RCC->APB1RSTR&=~(1<<19);//
	switch(baud_rate)
	{
		case BAUDRATE9600: UART4->BRR=0x0EA;break;
		case BAUDRATE115200: UART4->BRR=0x0138;break;
		default:
			 UART4->BRR=0x0138;break;//��������������Ϊ
	}
    UART4->CR1|=0x202c;//����ֹͣλ,���ý����ж�ʹ��
	NVIC_Set(2,1,52,2);//���ô����ж�
}

/*
PC12	TX
PD2		RX
*/
void UART5_Init(u32 baud_rate)
{
	RCC->APB2ENR |= 1 << 4;			//Enable PC clock
	RCC->APB2ENR |= 1 << 5;			//Enable PD clock
	
	GPIOC->CRH &= 0xfff0ffff;		//PC12 IO����
	GPIOC->CRH |= 0x000b0000;		
	
	GPIOD->CRL &= 0xfffff0ff;		//PD2  IO����
	GPIOD->CRL |= 0x00000400;
	
	RCC->APB1ENR	|= 1<<20; 		//����ʱ��ʹ��
	
    RCC->APB1RSTR	|= 1<<20;		//��λ����
    RCC->APB1RSTR	&= ~(1<<20);	
	
	switch(baud_rate)
	{
		case BAUDRATE9600: UART5->BRR=0x0EA;break;
		case BAUDRATE19200:	 UART5->BRR=0x753;break;
		case BAUDRATE115200: UART5->BRR=0x0138;break;
		default:
			 UART5->BRR=0x0138;break;//��������������Ϊ
	}
    UART5->CR1|=0x202c;//����ֹͣλ,���ý����ж�ʹ��
	NVIC_Set(2,1,53,0);//���ô����ж�
}




void UART1_Send(u8 tx_data)
{
	while((USART1->SR & (0x40)) == 0){}//�жϷ��ͻ�����Ϊ��
	 USART1->DR = tx_data;
}

void UART2_Send(u8 tx_data)
{
	while((USART2->SR & (0x40)) == 0){}//�жϷ��ͻ�����Ϊ��
	USART2->DR = tx_data;
}

void UART4_Send(u8 tx_data)
{
	while((UART4->SR & (0x40)) == 0);//�ȴ��������
	UART4->DR = tx_data;
}

void UART5_Send(u8 tx_data)
{
	while((UART5->SR & (0x40)) == 0);//�ȴ��������
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
