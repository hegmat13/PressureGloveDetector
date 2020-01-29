

#include <avr/io.h>
#include "pwm.h"

void initPWMTimer4(){
  DDRH |= (1 << DDH3); // output to pin 6 on the dev board

  // Timer 1: Set Fast PWM where OCR4A is the top value that TCNT4 counts up to, non-inverting
  TCCR4A |= (1 << COM4A1)|(1 << WGM41)|(1 << WGM40);
  TCCR4B |= (1 << WGM42)|(1 << CS41); // | (1 << WGM43);

  // duty cycle  = 25%
  OCR4A = 0;
}

void delayMS(unsigned int delay){
  for(unsigned int i = 0; i < delay; i++) {
  // calculate what value goes in OCR0A per microsecond
  OCR4C = 250;

  // Make sure the appropriate flag is down
  TIFR4 |= (1 << OCF4C);

  // Clear the timer
  TCNT4 = 0;

  // turn on the timer by setting the pre-scaler to 8
  TCCR4B |= (1 << CS41) | (1 << CS40);

  // while the flag is down, do not do anything.
  while(!(TIFR4 & (1 << OCF4C)));

  // Turn the clock back off
  TCCR4B &= ~(1 << CS42 | 1 << CS41 | 1 << CS40); }}



void changeFreq(int freq) {
  OCR4A = freq; 
}



/*
  if (freq == 0){
    OCR4A = 0; 
    return; 
  }

  for(int freq; freq < 255; freq++){
  OCR4A = freq; 
  if(freq == 254) {
    for(int i = 1; i < 255; i++){
    OCR4A = freq; 
    freq--; 
    }
    freq = 0; }}*/




