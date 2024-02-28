/*
 * File:   delay.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:39
 */


#include <xc.h>
#include "delay.h"

void delay_init() {
    T0CON0 = 0b10000000;
    T0CON1 = 0b01000011;
    
}

void delay(long long t, void (*f)()) {
    int total = 0;
    TMR0L = 0;
    PIR0bits.TMR0IF=0;
    
    while(t!=0) {
        while(total < 1000) {
            while(PIR0bits.TMR0IF==0) {
                total += (TMR0L - total);
                if(total >= 1000) break;
                if(f != NULL) f();
            }
            PIR0bits.TMR0IF = 0;
        }
        total = 0;
        t--;
    }
}
