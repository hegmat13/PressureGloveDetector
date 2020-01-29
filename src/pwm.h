

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void initPWMTimer4();
void delayMS(unsigned int delay); 
void changeFreq(int freq); 
void Chirp(); 

#endif
