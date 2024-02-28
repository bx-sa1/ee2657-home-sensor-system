/*
 * File:   main.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:47
 */


#include <xc.h>
#include "delay.h"
#include "lcd.h"

void main(void) {
    delay_init();
    lcd_init();
    
    for(;;) {
        lcd_display_cursor(0,0);
        lcd_display_message("Hello, World!");
        delay(60);
    }
}
