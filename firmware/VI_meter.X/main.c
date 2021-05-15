/* 
 * File:   main.c
 * Author: amit
 *
 * Created on May 22, 2016, 2:50 PM
 */
#include "system.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "adc.h"
#include "timer.h"


// PIC16F1827 Configuration Bit Settings

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

//=====================================================================================================================================
#define MIN_VALID_COUNT 80

void init_oscillater(void);
void init_gpio(void);
void fill_display_buff(void);

extern unsigned char flag_scan_adc;
extern unsigned int total_offset,display_offset;
extern float voltage,current;

unsigned char volt_buff[5] = {0},current_buff[5] = {0};
//========================================================================================================================================
int main(int argc, char** argv) {
    unsigned int fill_buffer_cntr = 0;
    
    init_oscillater();
    init_gpio();
    init_timer();
    init_adc();
    
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
//    __delay_ms();
    
    LATA = 0x08;
    
    while(1) {
        if(flag_scan_adc){
            flag_scan_adc = 0;
            scan_adc_chnl();
//            fill_display_buff();
            fill_buffer_cntr++;
            if(MIN_VALID_COUNT <= fill_buffer_cntr){
                fill_buffer_cntr = 0;
                fill_display_buff();
            }
        }
    }
}
//========================================================================================================================================
void init_oscillater(void) {
    OSCCONbits.IRCF = 14;           // 8 mhz
    OSCCONbits.SCS = 2;             // internal oscillater
    OSCCONbits.SPLLEN = 0;          // PLL disabled
//    OSCCON = 0X78;
}
//========================================================================================================================================
void init_gpio(void) {
    TRISB = 0x00;                   // port B as a output for display select

    TRISAbits.TRISA0 = 1;           // Analog input for current measurement
    TRISAbits.TRISA1 = 1;           // Analog input for voltage measurement
    TRISAbits.TRISA2 = 1;           // digital input 
    
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;

    TRISBbits.TRISB7 = 0;

    ANSELA = 0x00;
    ANSELB = 0x00;
}
//========================================================================================================================================
void fill_display_buff(void)
{
    unsigned int temp = 0;
    
    if(current < 10.0)temp = (current * 100);
    else if(current >= 100.0)temp = (current);
    else temp = (current * 10);
    current_buff[0] = temp / 100;
    temp = temp % 100;
    current_buff[1] = temp / 10;
    current_buff[2] = temp % 10;

    if(voltage < 10.0)temp = (voltage * 100);
    else if(voltage >= 100.0)temp = (voltage);
    else temp = (voltage * 10);
    volt_buff[0] = temp / 100;
    temp = temp % 100;
    volt_buff[1] = temp / 10;
    volt_buff[2] = temp % 10;
}

//========================================================================================================================================


//========================================================================================================================================



