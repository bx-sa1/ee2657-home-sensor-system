/*
 * File:   utils.C
 * Author: 2156982
 *
 * Created on 05 March 2024, 11:53
 */


#include <xc.h>
#include "utils.h"

int itoa(long long value, unsigned char *str) //absolute TODO: allow negative numbers
{
    char tmp[16];
    char *tp = tmp;
    
    int r;
    long long v = value;
    
    while(v || tp == tmp) {
        r = v % 10;
        v /= 10;
        *tp++ = r+'0';
    }
    
    if(v < 0) {
        *tp++ = '-';
    }
    
    int len = tp - tmp;
    
    while(tp > tmp) {
        *str++ = *--tp;
    }
    
    str[len] = 0x00;
    
    return len;
}

