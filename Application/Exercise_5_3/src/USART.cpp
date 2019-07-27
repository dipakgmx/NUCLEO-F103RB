//
// Created by dipak on 27/07/2019.
//

#include "../include/USART.h"
USART::USART(uint32_t baudrate)
    : baudrate(baudrate)
{
    // Enable clock for Port A, alternate functions and USART2

    //PORT A clock enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    //USART 2 clock enable
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    uint32_t val = SystemCoreClock;
    // PA2 (TxD) shall use the alternate function with push-pull
    GPIOA->CRL |= GPIO_CRL_CNF2_1;
    GPIOA->CRL |= GPIO_CRL_MODE2;

    // Enable transmitter, receiver and receive-interrupt of USART2
    GPIOA->CRL |= GPIO_CRL_CNF3_0;
    GPIOA->CRL &= ~GPIO_CRL_MODE3;


    // Set baudrate
    // 36000000/(115200*16) = 19.53125
    // 19 = 0x13
    // 0.53125 * 16 = 8.5 ~= 0x08

    USART2->BRR = 36000000/baudrate; //for 36MHZ on APB1 bus

    //----------  RX enable        TX enable     UART enable
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}
