/**** software delays different sw delays for PIC24FJ64GA004 set for FRCPLL with no clock div
 * changed to timer 2 because of secondary osc on timer 1 needed for RTCC
********************************************************************************************/
#include "delay.h"
#define iend 500
#define jend 1000



//timer1 hardware delays
void Delayms( unsigned t)
{
    T2CON = 0x8000;     // enable tmr1, Tcy, 1:1
    while (t--)
    {
        TMR2 = 0;
       // while (TMR1<8000);
        while( TMR2< REALCLK/COUNT1MS);

    }
} // Delayms
void Delay100us( unsigned t)
{
    T2CON = 0x8000;     // enable tmr1, Tcy, 1:1
    while (t--)
    {
        TMR2 = 0;
       // while (TMR1<8000);
        while( TMR2< REALCLK/COUNT100US);

    }
} 
void Delay10us( unsigned t)
{
    T2CON = 0x8000;     // enable tmr1, Tcy, 1:1
    while (t--)
    {
        TMR2 = 0;
       // while (TMR1<8000);
        while( TMR2< REALCLK/COUNT10US);

    }
} //
//software delay
	void delay_1us(void) {
		int j;
			for (j=0;j<1; j++);
	}
	

