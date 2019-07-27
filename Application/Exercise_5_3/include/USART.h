//
// Created by dipak on 27/07/2019.
//

#ifndef EXERCISE_5_3_USART_H
#define EXERCISE_5_3_USART_H
#include "stm32f1xx.h"

class USART
{
public:
    USART(uint32_t baudrate);
private:
    uint32_t baudrate;

};

#endif //EXERCISE_5_3_USART_H
