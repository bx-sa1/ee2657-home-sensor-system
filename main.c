/*
 * File:   main.c
 * Author: 2156982
 *
 * Created on 28 February 2024, 13:47
 */

// PIC16F18877 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = ECH    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with OSCFRQ= 32 MHz and CDIV = 1:1)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "sensors.h"
#include "utils.h"
#include "keypad.h"

int read_pin() {
    const char *actual_pin = "123456";
    char pin[7];
    char *pin_p = pin;
    uint8_t pin_val[6];
    uint8_t *pin_val_p = pin_val;
    uint8_t count = 0;
    
    while(count < 6) {
        keypad_scan();
        if(keypad_read(pin_val_p+count, pin_p+count)) {
            count++;
            lcd_char('*');
        }
        delay(100, NULL);
    }
    pin_p[6] = '\0';
    
    for(int i = 0; i < 7; i++){
        if(pin[i] != actual_pin[i]) {
            return 0;
        }
    }
    
    return 1;
}

enum State {
    LOGIN,
    HUMIDITY,
    TEMPERATURE,
    
};

void main(void) {
    TRISB = 0x00;
    TRISA = 0b00000111;
    ANSELA = 0x00;
    INTCONbits.GIE = 1;
    delay_init();
    lcd_init();
    sensors_init();
    
    enum State state = LOGIN;
    
    for(;;) {
        switch(state) {
            case LOGIN:
                lcd_display_cursor(0,0);
                lcd_display_message("Welcome!");
                lcd_display_cursor(1,0);
                lcd_display_message("Enter PIN:");
                if(!read_pin()) {
                    lcd_clear();
                    lcd_display_cursor(0,0);
                    lcd_display_message("PIN is incorrect");
                    delay(5000, NULL);
                    lcd_clear();
                } else {
                    state = HUMIDITY;
                    lcd_clear();
                }
                break;
            case HUMIDITY:
                lcd_display_cursor(0, 0);
                lcd_display_message("Hmd: ");
                
                uint8_t hq = 0, hr = 0;
                sensors_read_humidity(&hq, &hr);
                char hqc[4]; itoa(hq, hqc);
                char hrc[3]; itoa(hr, hrc);
                lcd_display_message(hqc);
                lcd_display_message(".");
                lcd_display_message(hrc);
                lcd_display_message("%RH");
                break;
            case TEMPERATURE:
                lcd_display_cursor(0, 0);
                lcd_display_message("Temp: ");
                
                uint8_t tq = 0, tr = 0;
                sensors_read_temperature(&tq, &tr);
                char tqc[4]; itoa(tq, tqc);
                lcd_display_message(tqc);
                break;   
        }
        
        if(state != LOGIN) {
            uint8_t kv, k;
            keypad_scan();
            if(keypad_read(&kv, &k)) {
                switch(kv) {
                    case 1:
                        lcd_clear();
                        state = HUMIDITY;
                        break;
                    case 2:
                        lcd_clear();
                        state = TEMPERATURE;
                        break;
                }
            }
        }
    }
}
