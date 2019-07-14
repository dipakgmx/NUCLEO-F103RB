#include <stm32f1xx.h>

int main()
{
    bool button_status;
    // I/O port A and C clock enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;

    // Configure Pins
    // User LD2 LED (PA5 Pin)
    GPIOA->CRL &= ~GPIO_CRL_CNF5;
    GPIOA->CRL |= GPIO_CRL_MODE5_0;

    //Button B1 USER (PC13 Pin)
    GPIOC->CRH = GPIO_CRH_CNF13_0;
    GPIOC->CRH &= ~GPIO_CRH_MODE13_Msk;

    while (true) {
        button_status = ((GPIOC->IDR & GPIO_IDR_IDR13) == 0);
        if (button_status)
            GPIOA->BSRR = GPIO_BSRR_BS5;
        else
            GPIOA->BRR = GPIO_BRR_BR5;
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
    while (1);
}
#endif