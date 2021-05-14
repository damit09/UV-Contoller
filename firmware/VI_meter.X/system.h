/* 
 * File:   system.h
 * Author: amit
 *
 * Created on May 22, 2016, 3:12 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ  8000000

#define SEL_DISP_ONE()          {LATB &= 0XC0;\
                                 LATB |= 0X01;}
#define SEL_DISP_TWO()          {LATB &= 0XC0;\
                                 LATB |= 0X02;}
#define SEL_DISP_THREE()        {LATB &= 0XC0;\
                                 LATB |= 0X04;}
#define SEL_DISP_FOUR()         {LATB &= 0XC0;\
                                 LATB |= 0X08;}
#define SEL_DISP_FIVE()         {LATB &= 0XC0;\
                                 LATB |= 0X10;}
#define SEL_DISP_SIX()          {LATB &= 0XC0;\
                                 LATB |= 0X20;}
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

