#include "system.h"
#include <xc.h>
#include <float.h>
#include <math.h>
#include "timer.h"
#include "adc.h"
//==========================================================================================================================================
#define REF_OFFSET              612//510
#define ADC_RESOLUTION          4.00//5.034//4.88
#define VOLT_CALIB_FACTOR       34.0
#define CURRENT_CALIB_FACTOR    185
//==========================================================================================================================================
float AN0_volt_chnl = 0,AN1_current_chnl = 0,voltage = 1.5,current = 15.5,display_offset = 0,total_offset = 0;
unsigned int AN0_adc_chnl = 0,AN1_adc_chnl = 0;
unsigned char switch_detect_cntr = 0;
//==========================================================================================================================================
void init_adc(void) {
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;

    ADCON0 = 0X00;
    ADCON1bits.ADPREF = 3;          // internal FVR as a positive reference 
    ADCON1bits.ADCS = 2;            // Fosc/4
    ADCON1bits.ADFM = 1;            // right justified
    ADCON0bits.CHS = VOLTAGE_CHNL;
    FVRCONbits.FVREN = 1;
    FVRCONbits.ADFVR = 3;
    ADCON0bits.ADON = 1;
}
//==========================================================================================================================================
void scan_adc_chnl(void)
{    
    float temp_current_val = 0;

    switch(ADCON0bits.CHS){
        case VOLTAGE_CHNL:  AN0_adc_chnl = read_adc(VOLTAGE_CHNL);
                            AN0_volt_chnl = ((AN0_volt_chnl * 9) + AN0_adc_chnl);
                            AN0_volt_chnl = (AN0_volt_chnl / 10);
                            voltage = ((AN0_volt_chnl * ADC_RESOLUTION));
                            voltage = ((voltage * VOLT_CALIB_FACTOR) / 1000);
                            //voltage = display_offset;
                            ADCON0bits.CHS = CURRENT_CHNL;
                            break;
        case CURRENT_CHNL:  AN1_adc_chnl = read_adc(CURRENT_CHNL);
                            AN1_current_chnl = ((AN1_current_chnl * 49) + AN1_adc_chnl);
                            AN1_current_chnl = (AN1_current_chnl / 50);
//                            current = AN1_current_chnl;
                            temp_current_val = (AN1_current_chnl - REF_OFFSET);
                            temp_current_val = ((temp_current_val * ADC_RESOLUTION) / CURRENT_CALIB_FACTOR);

                            if(!PORTAbits.RA2)switch_detect_cntr++;
                            else switch_detect_cntr = 0;
                            if(switch_detect_cntr >= 100){
                                switch_detect_cntr = 0;
                                display_offset = temp_current_val;
                            }
                            current = temp_current_val - display_offset;
                            if(current <= 0.10)current = 0;
                            //current = AN1_current_chnl;
                            ADCON0bits.CHS = VOLTAGE_CHNL;
                            break;
    }
}
//==========================================================================================================================================
unsigned int read_adc(unsigned char chnl_no)
{
    unsigned int result = 0;

    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);

    result = ADRESH;
    result <<= 8;
    result &= 0x0300;
    result |= ADRESL;
//    result &= 0x03FF;
    return(result);
}
//==========================================================================================================================================


//==========================================================================================================================================
