#include <stm32f1xx.h>

#ifdef __cplusplus
extern "C" {
#endif
void SysTick_Handler(void);
#ifdef __cplusplus
}
#endif

void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

static __IO uint32_t TimingDelay;

int main()
{
    bool button_status;
    // I/O port C clock enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;


    // Configure Pins
    // User LD2 LED (PA5 Pin)
    GPIOA->CRL &= ~GPIO_CRL_CNF5;
    GPIOA->CRL |= GPIO_CRL_MODE5_0;

    // Configure ticks to ms
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1);
    }

    while(1)
    {
        GPIOA->BSRR = (1<<5);
        Delay(500);
        GPIOA->BRR = (1<<5);
        Delay(500);
    }
}

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

void Delay(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }

}

#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
    while (1);
}
#endif