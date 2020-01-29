// Description: This file describes functions used by the timer
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();
void initTimer1();
void delayMs(unsigned int delay);
void delayUs(unsigned int delay);

#endif
