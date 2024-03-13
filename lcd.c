/*
 * File:   lcd.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:39
 */

#include <xc.h>
#include "lcd.h"
#include "delay.h"

void lcd_cmd(unsigned char cmd)
{
    LATB = 0x20 + ((cmd >> 4) & 0x0f); // enable + MSB of instruction
    LATB = (cmd >> 4) & 0x0f; // sent
    delay(1, NULL);
    LATB = 0x20 + (cmd & 0x0f); // enable + LSB
    LATB = cmd & 0x0f; // sent
    delay(1, NULL);
}


void lcd_init() {
    delay(600, NULL);
    LATB = 0x23;
    LATB = 0x03;
    delay(200, NULL);
    LATB = 0x22;
    LATB = 0x02;
    delay(50, NULL);
    LATB = 0x22;
    LATB = 0x02;
    delay(50, NULL);
    
    lcd_cmd(0x28);
    lcd_cmd(0x0f);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
}

void lcd_char(unsigned char c)
{
    LATB = 0x30 + ((c >> 4) & 0x0f); // enable + MSB of char
    LATB = 0x10 + ((c >> 4) & 0x0f); // sent
    delay(1, NULL);
    LATB = 0x30 + (c & 0x0f); // enable + LSB of char
    LATB = 0x10 + (c & 0x0f); //sent
    delay(1, NULL);
}

void lcd_display_message(const unsigned char * mess)
{
    unsigned int i=0;
    while(mess[i] != 0)
    {
        lcd_char(mess[i]);
        i++;
    }
}

void lcd_display_cursor(unsigned char line, unsigned char position)
{
    if(line==0) 
    {
        position = position + 0x00; 
    } else if(line==1) {
        position = position + 0x40;
    } else if(line==2) {
        position = position + 0x14;
    } else if(line==3) {
        position = position + 0x54;
    }
    lcd_cmd(0x80+position);
}

