#include "system.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "timer.h"
//=========================================================================================================================================
void display_data(void);
//=========================================================================================================================================
extern float voltage,current;
unsigned char flag_scan_adc = 0;
extern unsigned char volt_buff[5],current_buff[5];
unsigned char select_display = 1,temp_copy = 0,scan_adc_counter = 0;
unsigned int msec_counter = 0;
//=========================================================================================================================================
void interrupt systeam_ISR(void) {
    
    if(PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0XF8;
        TMR1L = 0X2F;

        msec_counter++;
        if(msec_counter >= 2) {
            msec_counter = 0;
            switch(select_display) {
                case 1: LATA3 = 1;
                        LATB &= 0XC0; 
                        temp_copy = volt_buff[0];
                        display_data();
                        SEL_DISP_ONE();
                        if(voltage < 10.0)LATA3 = 0;
                        select_display = 2;  
                        break;
                case 2: LATA3 = 1;
                        LATB &= 0XC0;
                        if(volt_buff[1] == 0 && volt_buff[2] == 0)temp_copy = 0X0F;
                        else temp_copy = volt_buff[1];
                        display_data();
                        SEL_DISP_TWO();
                        if(voltage >= 10.0 && voltage < 100.0)LATA3 = 0;
                        select_display = 3;
                        break;
                case 3: LATA3 = 1;
                        LATB &= 0XC0;
                        if(volt_buff[1] == 0 && volt_buff[2] == 0)temp_copy = 0X0F;
                        else temp_copy = volt_buff[2];
                        display_data();
                        SEL_DISP_THREE();
                        select_display = 4;
                        break;
                case 4: LATA3 = 1;
                        LATB &= 0XC0;
                        temp_copy = current_buff[0];
                        display_data();
                        SEL_DISP_FOUR();
                        if(current <= 10.0)LATA3 = 0;
                        select_display = 5;
                        break;
                case 5: LATA3 = 1;
                        LATB &= 0XC0;
                        if(current_buff[1] == 0 && current_buff[2] == 0)temp_copy = 0X0F;
                        else temp_copy = current_buff[1];
                        display_data();
                        SEL_DISP_FIVE();
                        if(current >= 10.0 && current < 100.0)LATA3 = 0;
                        select_display = 6;
                        break;
                case 6: LATA3 = 1;
                        LATB &= 0XC0;
                        if(current_buff[1] == 0 && current_buff[2] == 0)temp_copy = 0X0F;
                        else temp_copy = current_buff[2];
                        display_data();
                        SEL_DISP_SIX();
                        select_display = 1;
                        break;
            }
        }
        scan_adc_counter++;
        if(scan_adc_counter >= 10){
            scan_adc_counter = 0;
            flag_scan_adc = 1;
        }
    }
}
//=========================================================================================================================================
void display_data(void) {

    temp_copy = temp_copy << 4;
    temp_copy = temp_copy & 0XF0;
    LATA &= 0X0F;
    LATA |= temp_copy;
//    LATA |= 0x08;
    temp_copy = temp_copy & 0x20;
    if(temp_copy == 0x20)LATBbits.LATB7 = 1;
    else LATBbits.LATB7 = 0;
}