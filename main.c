/*
 * File:   main.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:47
 */


#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "tempandhum.h"
#include "utils.h"

void read_sensors() {
    
}

void main(void) {
    INTCONbits.GIE = 1;
    delay_init();
    lcd_init();
    adc_init();
    
    for(;;) {
        lcd_display_cursor(0,0);
        lcd_display_message("Hello, World!");
        
        unsigned int temp = read_temperature();
        char temp_string[16];
        itoa(temp, temp_string);
        lcd_display_cursor(1,0);
        lcd_display_message(temp_string);
    
        delay(5000, NULL);
    }
}
