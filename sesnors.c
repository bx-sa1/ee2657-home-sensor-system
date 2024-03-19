/*
 * File:   tempandhum.c
 * Author: 2156982
 *
 * Created on 05 March 2024, 11:17
 */

#include <xc.h>
#include "sensors.h"
#include "utils.h"

#define ADPCH_ANC7 0b010111
#define ADPCH_ANC6 0b010110
#define ADPCH_ANC5 0b010101

#define TEMP_MAX 125
#define TEMP_MIN -40

void sensors_init() {
    ADCON0 = 0b10000100;
    ANSELC = 0b11100000; // Set AN07 and AN6 pin as analog
    TRISC = 0b11100000; //01111000
}

void sensors_read_temperature(uint8_t *celsius_q, uint8_t *celsius_r) {
    ADPCH = ADPCH_ANC7;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    uint16_t temp = ((ADRESH << 8) + ADRESL);
    *celsius_q = temp;
    *celsius_r = temp;
}

void sensors_read_humidity(uint8_t *humidity_q, uint8_t *humidity_r) {
    ADPCH = ADPCH_ANC6;
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    uint16_t humidity = ((ADRESH << 8) + ADRESL);
    *humidity_q = FROM_FIXED(((TO_FIXED(humidity)/TO_FIXED(1023)) * TO_FIXED(127)) + 20);
    *humidity_r = FROM_FIXED(REMAINDER_FROM_FIXED(((TO_FIXED(humidity)/TO_FIXED(1023)) * TO_FIXED(127)) + 20));
}
