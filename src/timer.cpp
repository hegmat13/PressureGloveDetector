#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode
*/
void initTimer0(){
  TCCR0A |= (1 << WGM01);}


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode 
*/
void initTimer1(){
  TCCR1A |= (1 << WGM11);} 

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for 125
* 100 milliseconds
*/
void delayMs(unsigned int delay){
  for(unsigned int i = 0; i < delay; i++) {
  // calculate what value goes in OCR0A per microsecond
  OCR0A = 250;

  // Make sure the appropriate flag is down
  TIFR0 |= (1 << OCF0A);

  // Clear the timer
  TCNT0 = 0;

  // turn on the timer by setting the pre-scaler to 8
  TCCR0B |= (1 << CS01) | (1 << CS00);

  // while the flag is down, do not do anything.
  while(!(TIFR0 & (1 << OCF0A)));

  // Turn the clock back off
  TCCR0B &= ~(1 << CS02 | 1 << CS01 | 1 << CS00); }}



/* This delays the program in microseconds by amount specified in delay
*/
void delayUs(unsigned int delay){     //Delay in microseconds
  
for(int i = 0; i < delay; i++) { 
  //calculate number of ticks

TCNT1 = 0;
  // clear the timer

OCR1AH = 0;
OCR1AL = 2; 
  // calculate the TOP value and assign it to OCR1A (OCR1AH and OCR1AL)

TCCR1B |= (1 << CS11);
  // Turn on the timer, this prescaler is 8

while(!(TIFR1 & (1 << OCF1A)));
  // Do nothing while the OCF1A flag = 0 or is triggered/down. 

 TCCR1B &= ~(1 << CS12 | 1 << CS11 | 1 << CS10);  }}  // Turn off the timer 
