
#include "system.h"
#include <xc.h>
#include "timer.h"
#include "adc.h"
//========================================================================================================================================
void init_timer(void) {
    T1CONbits.T1CKPS = 0;       // 1:1
    T1CONbits.TMR1CS = 0;       // Fosc/4

    TMR1H = 0XF8;
    TMR1L = 0X2F;
    PIE1bits.TMR1IE = 1;        // timer 1 interrupt enabled
    PIR1bits.TMR1IF = 0;        // clear interrupt flag
    T1CONbits.TMR1ON = 1;       // timer -1 on
}
