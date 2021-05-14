/* 
 * File:   adc.h
 * Author: amit
 *
 * Created on May 22, 2016, 3:01 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define VOLTAGE_CHNL      0
#define CURRENT_CHNL      1 
    
void init_adc(void);
void scan_adc_chnl(void);
unsigned int read_adc(unsigned char chnl_no);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

