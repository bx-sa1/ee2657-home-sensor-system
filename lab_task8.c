/*
 * File:   lab_task2.c
 * Author: 2156982
 *
 * Created on 06 February 2024, 09:46
 */


// PIC16F18877 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with OSCFRQ= 32 MHz and CDIV = 1:1)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config LPBOREN = ON     // Low-Power BOR enable bit (ULPBOR enabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = OFF    // Peripheral Pin Select one-way control (The PPSLOCK bit can be set and cleared repeatedly by software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (High Voltage on MCLR/Vpp must be used for programming)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <delay.h>
//#include <math.h>

#define SHIFT_AMMOUNT 16
#define SHIFT_MASK ((1 << SHIFT_AMMOUNT) - 1)


int itoa(long long value, unsigned char *str) //absolute
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
    
    int len = tp - tmp;
    
    while(tp > tmp) {
        *str++ = *--tp;
    }
    
    str[len] = 0x00;
    
    return len;
}
 
/* int ftoa(float n, unsigned char* res, int dp) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
 
    // Extract floating part 
    float fpart = n - (float)ipart; 
 
    // convert integer part to string 
    int i = itoa(ipart, res, 0); 
 
    if(dp != 0) {
        res[i] = '.'; // add dot 
        i += 1;

        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, dp); 

        i = itoa((int)fpart, res + i, dp); 
    }
    
    return i;
} */

void main(void) {
    TRISB = 0; 
    ADPCH=0x00;  // use ANA0 channel 
    ADCON0 = 0b10000100;
    lcd_init();
    
    while(1)
    {
        ADCON0bits.ADGO=1;             // start the conversion 
        while(ADCON0bits.ADGO);     // wait for conversion to complete 
        int result = ((ADRESH << 8) | ADRESL);
        long long res_v_q = (result*5) / 1023;
        long long res_v_r = (result*5) % 1023;
        
        unsigned char res_str[16];
        unsigned char res_v_str[32];
        int res_len = itoa(result, res_str);
        int res_v_len = itoa(res_v_q, res_v_str);
        res_v_str[res_v_len++] = '.';
        res_v_len += itoa((res_v_r*100)/1023, res_v_str + res_v_len);
        
        display_cursor(0,0);
        display_message("ADC Result:");
        display_cursor(2,0);
        display_message(res_str);
        display_cursor(3,0);
        display_message(res_v_str);
        display_cursor(3,5);
        display_message("V");
        delay_lcd(60);
    }
    return;
}