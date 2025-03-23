#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include "lcd.h"  

#define BLUE     _BV(PB0)
#define BLACK    _BV(PB1)
#define RED      _BV(PB2)
#define YELLOW   _BV(PB3)

#define BT1 PC3
#define BT2 PC4

#define DELAY 2 /* milliseconds between steps */

uint8_t pressed1();
uint8_t pressed2();
void full_rotation();
void uintToStr(unsigned int num , char str[9]);

int main(void)
{
    unsigned int price = 0 ; 
    char buff[9];
    DDRC &=  (~(0x18)) ;  // buttons as in put

    PORTC |= (1 << BT1) | (1 << BT2); //activate input pull up
     
    DDRB = 0xff;      /* Set PORTB as output (aka stepper pins) */
    PORTB = 0x00;     /* Initialize PORTB to 0 */
    LCD_Init();       
    
    
    
    LCD_String_xy(0, 0, "eswara jamila");   /* Display string on the first line of LCD */
    LCD_String_xy(1,0, "prix:");
    LCD_String_xy(1,14, "DA");
   
    
    while(1)  /* Infinite loop to control the LED states */
    {
	 uintToStr(price,buff);
	 LCD_String_xy(1,5,buff);
	 if(pressed1()){
	    price+=500;
	 }
	 
	 if(pressed2()){
	    if(price >= 500){
	    price-=500;
	    }
	 }
        full_rotation();
	
	
	
    }
}


// price to string
void uintToStr(unsigned int num , char str[9]){
   int i = 8;
   
   do{
      str[i-1] = (num % 10) + '0' ; 
      i--;
      num/=10;
   }while(i > 0 );
   
   str[8]='\0';
   
   
}




void full_rotation(){
	 PORTB = BLUE;
        _delay_ms(DELAY); 
        
        PORTB = BLUE | BLACK;
        _delay_ms(DELAY);       
        
        PORTB = BLACK;
        _delay_ms(DELAY);        
        
        PORTB = RED | BLACK;
        _delay_ms(DELAY);
        
        PORTB = RED;
        _delay_ms(DELAY);
        
        PORTB = RED | YELLOW;
        _delay_ms(DELAY);
        
        PORTB = YELLOW;
        _delay_ms(DELAY);
        
        PORTB = YELLOW | BLUE;
        _delay_ms(DELAY);

}



//button read functions

uint8_t pressed1(){
   if(!(PINC & (1 << BT1) )){
      _delay_ms(50);
      if(!(PINC & (1 << BT1) )){
	 while (!(PINC & (1 << BT1) )){;}
	 //wait for release xdxd
	 return 1;
      }
   }
   return 0 ;
}

uint8_t pressed2(){
   if(!(PINC & (1 << BT2) )){
      _delay_ms(50);
      if(!(PINC & (1 << BT2) )){
	 while (!(PINC & (1 << BT2) )){;}
	 //wait for release xdxd
	 return 1;
      }
   }
   return 0 ;
}