


#include "adc.h"
#include <avr/io.h>

void initADC7() {
  // set voltage references to be AVCC
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  // ADLAR = 0 (RIGHT JUSTIFIED)
  ADMUX &= ~(1 << ADLAR);

  // Set ADC7 as single-ended input with MUX[5:0] = 0b000111
  ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
  ADMUX &=  ~(1 << MUX4);
  ADMUX &=  ~(1 << MUX3);
  ADCSRB &= ~(1 << MUX5);

  // set Auto Trigger Source Selection
  // set to free-running mode ADTS[2:0] = 0b000
  // 
  
  //Enable ADC interrupt 
  ADCSRA |= (1 << ADIE); 
  
  //Compare on output match for Timer1
  ADCSRB |= (1 << ADTS2);
  ADCSRB &= ~(1 << ADTS1);
  ADCSRB |= (1 << ADTS0);

  //enable auto-triggering and turn-off ADC
  ADCSRA |= (1 << ADATE); 
  ADCSRA |= (1 << ADEN);

  // set the pre-scaler to 128
  // Sampling frequency is 16 Mhz divided by pre-scaler = 125KHz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // disable ADC0 pin digital input - pin A0 on board
  DIDR0 |= (1 << ADC7D);

  // start the first conversion
  ADCSRA |= (1 << ADSC);
}