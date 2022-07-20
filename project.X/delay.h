
#ifndef __DELAY_H__
#define __DELAY_H__
#include <plib.h>
#define SYS_CLK (8000000L) //8 Mhz internal fast oscillator
#define PB_DIV 1
#define PRESCALE 1
#define REALCLK SYS_CLK/PB_DIV/PRESCALE
#define COUNT1MS 1000
#define COUNT100US 10000
#define COUNT10US 60000/2
//hardware Timer 1 based delays
    void Delayms( unsigned t);
    void Delay100us( unsigned t);
    void Delay10us( unsigned t);

	void delay_1us(void);  //used in LCD for E
	

#endif
