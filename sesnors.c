/*
 * File:   tempandhum.c
 * Author: 2156982
 *
 * Created on 05 March 2024, 11:17
 */

#include <xc.h>
#include "sensors.h"

#define TEMP_MAX 125
#define TEMP_MIN -40

void sensors_init() {
    ADCON0 = 0b10000100;
    ANSELC = 0b00000110; // Set AN0 and AN1 pin as analog
    TRISC = 0b00000110; //01111000
}

void sensors_read_temperature(uint8_t *celsius_q, uint8_t *celsius_r) {
    ADPCH = 0b010011;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    uint16_t temp = ((ADRESH << 8) + ADRESL);
    *celsius_q = (TEMP_MAX / 1024) * (temp + TEMP_MIN);
    *celsius_r = (TEMP_MAX % 1024) * (temp + TEMP_MIN);
}

void sensors_read_humidity(uint8_t *humidity_q, uint8_t *humidity_r) {
    ADPCH = 0b010001;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    uint16_t humidity = ((ADRESH << 8) + ADRESL);
    *humidity_q = humidity/1024;
    *humidity_r = humidity%1024;
}
