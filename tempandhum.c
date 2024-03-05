/*
 * File:   tempandhum.c
 * Author: 2156982
 *
 * Created on 05 March 2024, 11:17
 */


#include <xc.h>
#include "tempandhum.h"

void adc_init() {
    ADCON0 = 0b1000100;
    ANSELAbits.ANSELA = 0b00000011; // Set AN0 and AN1 pin as analog
}

unsigned int read_temperature() {
    ADPCH = 0b000000;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    unsigned int temp = ((ADRESH << 8) + ADRESL);
    unsigned int kelvin = (temp * 1000) / 10;
    return kelvin;
}

unsigned int read_humidity() {
    ADPCH = 0b000001;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    unsigned int humidity_v = ((ADRESH << 8) + ADRESL);
    return humidity_v;
}
