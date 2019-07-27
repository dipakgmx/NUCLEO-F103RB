#include "stm32f1xx.h"
#include "../include/USART.h"

int main(void)
{
    USART usart(115200);

    while (1) {
        if (USART2->SR & USART_SR_RXNE) //if RX is not empty
        {
            char temp = USART2->DR; //fetch the data received
            USART2->DR = temp;
            while (!(USART2->SR & USART_SR_TC)) //wait for TX to be complete
                ;
        }
    };
}