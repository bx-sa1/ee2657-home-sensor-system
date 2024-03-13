/*
 * File:   delay.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:39
 */


#include <xc.h>
#include "delay.h"

long long delay_time = 0;

void __interrupt() isr(void) {
    TMR0L = 156;
    PIR0bits.TMR0IF = 0;
    if(delay_time != 0) {
        delay_time--;
    }
}

void delay_init() {
    T0CON0 = 0b10000000;
    T0CON1 = 0b01000101;
    PIE0bits.TMR0IE = 1;
}

void delay(long long t, void (*f)(void)) {
    TMR0L = 0;
    PIR0bits.TMR0IF=0;
    
    delay_time = t;
    
    while(delay_time != 0) {
        if(f != NULL) {
            (*f)();
        }
    }
}
