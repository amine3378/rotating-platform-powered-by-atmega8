#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include "lcd.h"  

#define BLUE     _BV(PB0)
#define BLACK    _BV(PB1)
#define RED      _BV(PB2)
#define YELLOW   _BV(PB3)

#define DELAY 60 /* milliseconds between steps */

int main(void)
{
    DDRB = 0xff;      /* Set PORTB as output */
    PORTB = 0x00;     /* Initialize PORTB to 0 */
    LCD_Init();       /* Initialize the LCD */
    
    LCD_String_xy(0, 0, "eswara jamila");   /* Display string on the first line of LCD */
    
    while(1)  /* Infinite loop to control the LED states */
    {
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
}
 