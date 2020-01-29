#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

/*
 * Initializes all pins related to the LCD to be outputs
 */
void initLCDPins(){
  DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
  DDRB |= (1 << DDB4) | (1 << DDB6);
}

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay)
{

  PORTA = data; //asser lower bits 

 
  PORTB &= ~(1 << PORTB4);  //Set RS to low

  
  PORTB |= (1 << PORTB6);//Set Enable to high
  delayUs(1); //delay for 1 us
  PORTB &= ~(1 << PORTB6); //Set Enable to Low

  delayUs(delay); //delay per amount sent from main
  
}

/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  
  PORTA = command >> (int)4; //assert top four bits
  
  PORTB &= ~(1 << PORTB4); //set RS to Low

  
  
  PORTB |= (1 << PORTB6); //set enable to High
  delayUs(1); //delay 1 us
  PORTB &= ~(1 << PORTB6); //set enable to Low
  
  PORTA = command; //assert bottom four bits

 
  //Set enable to high
  PORTB |= (1 << PORTB6); //set enable to High
  delayUs(1); //delay 1 us
  PORTB &= ~(1 << PORTB6); //set enable to Low
  
  delayUs(delay); //delay by amount sent from main

}

/* Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void writeCharacter(unsigned char character){
  
 
 
  PORTA = character >> (int)4; //Assert top 4 bits
  

  
  PORTB |= (1 << PORTB4);//Set RS to high

 
 
  PORTB |= (1 << PORTB6); //Set Enable to high
  delayUs(1); //Delay 1 us
  PORTB &= ~(1 << PORTB6);  //Set Enable to low
  

  PORTA = character; //Assert lower 4 bits
  

  
  PORTB |= (1 << PORTB6); //Set Enable to high
  

  delayUs(1); //delay 1 us
  PORTB &= ~(1 << PORTB6); //Set Enable to low
  delayUs(46);   //Delay by 46 microseconds

}

/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void writeString(const char *string){
  
  //While not at the end of the string repeat
  while (*string != '\0')
  {
    
    writeCharacter(*string); //Call WriteCharacter for current string
    string++; //increment and move on to next character if not null
  }

}

/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void moveCursor(unsigned char x, unsigned char y){
  

  if(x==0)
  {
    eightBitCommandWithDelay((0x80 | y), 50); //if not moving in x direction, move in y direction
  }

  else{
    eightBitCommandWithDelay((0xC0 | y), 50); //move in x direction
  }
}


/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  // Delay 15 milliseconds
  //Changed to 50 ms per instructions in class
  delayUs(50000);

  // Write 0b0011 to DB[7:4] and delay 4100 microseconds
  fourBitCommandWithDelay(0b0011, 4100);
  
  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0b0011, 100);

  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  // write 0b0011 to DB[7:4] and no delay
  
  //Used 100 us per instructions in class
  fourBitCommandWithDelay(0b0011, 100);

  // write 0b0010 to DB[7:4] and delay.
  
  //CHanged delay per instuctions in class
  fourBitCommandWithDelay(0b0010, 100);

  //Changed delay to 53 per class instruction
  // Function set in the command table
  eightBitCommandWithDelay(0b00101000, 53);

  // Display off in the command table
  //Changed delay time per class instruction
  eightBitCommandWithDelay(0b00001000, 53);

  // Clear display in the command table. Remember the delay is longer!!!
  //Changed delay from 1640 per class instruction
  eightBitCommandWithDelay(0b00000001, 3000);

  // Entry Mode Set in the command table.
  //Delay changed from 40 per class instruction
  eightBitCommandWithDelay(0b00000110, 53);

  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  //Changed delay from 40 per class instructions and correct instruction from 15
  eightBitCommandWithDelay(0b00001101, 53); //blinking cursor

}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}
