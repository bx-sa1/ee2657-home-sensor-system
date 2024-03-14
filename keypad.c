/*
 * File:   keypad.c
 * Author: 2156982
 *
 * Created on 12 March 2024, 11:09
 */


#include <xc.h>
#include "keypad.h"

#define X3 PORTAbits.RA0
#define X2 PORTAbits.RA1
#define X1 PORTAbits.RA2
#define Y4 PORTAbits.RA3
#define Y3 PORTAbits.RA4
#define Y2 PORTAbits.RA5
#define Y1 PORTAbits.RA6

void keypad_scan() {
    static uint8_t key_scan = 0x08;
    
    key_scan = key_scan << 1;
    
    if(key_scan >= 0x80) {
        key_scan = 0x08;
    }
    
    LATA = key_scan;
}

int keypad_read(uint8_t *value, char *char_value) {
    if((PORTA & 0x07) != 0) {
        switch(PORTA) {
            case 0b01000100:
                *char_value = '1';
                *value = 1;
                break;
            case 0b01000010:
                *char_value = '2';
                *value = 2;
                break;
            case 0b01000001:
                *char_value = '3';
                *value = 3;
                break;
            case 0b00100100:
                *char_value = '4';
                *value = 4;
                break;
            case 0b00100010:
                *char_value = '5';
                *value = 5;
                break;
            case 0b00100001:
                *char_value = '6';
                *value = 6;
                break;
            case 0b00010100:
                *char_value = '7';
                *value = 7;
                break;
            case 0b00010010:
                *char_value = '8';
                *value = 8;
                break;
            case 0b00010001:
                *char_value = '9';
                *value = 9;
                break;
            case 0b00001100:
                *char_value = '*';
                *value = 11;
                break;
            case 0b00001010:
                *char_value = '0';
                *value = 10;
                break;
            case 0b00001001:
                *char_value = '#';
                *value = 12;
                break;
            default:
                return 0;
        }
        
        return 1;
    }
    
    return 0;
}
