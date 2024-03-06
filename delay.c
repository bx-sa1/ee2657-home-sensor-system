/*
 * File:   delay.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:39
 */


#include <xc.h>
#include "delay.h"

unsigned int delay_time = 0;

void __interrupt() isr() {
    TMR0L = 156;
    PIR0bits.TMR0IF = 0;
    if(delay != 0) {
        delay_time--;
    }
}

void delay_init() {
    T0CON0 = 0b10000000;
    T0CON1 = 0b01001010;
    PIE0bits.TMR0IE = 1;
}

void delay(long long t, void (*f)()) {
    int total = 0;
    TMR0L = 0;
    PIR0bits.TMR0IF=0;
    
    delay_time = t*10;
    
    while(delay_time != 0) {
        if(f != NULL) {
            f();
        }
    }
}
