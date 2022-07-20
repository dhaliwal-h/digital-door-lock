//#include "p24hxxxx.h"
#include <plib.h>
#include "adc.h"
char bcd10000 =0;
char bcd1000 =0;
char bcd100 =0 ;
char bcdtens =0 ;
char bcdunits =0;
int average =0;
float degree =0;

int adcvalue =0;

char count[] = {'0','0','0','0',' ', '0','0','0','D','E','G',' '};
void initADC( int ANpin)
{
	AD1CON1bits.ADON = 0; // turn off the ADC
    //AD1PCFG = 0xF8CF;    // select analog input pins
//pin_set( ANpin);
        TRISBbits.TRISB15=1;
     //   TRISBbits.TRISB14 =1;
     //    TRISBbits.TRISB13 =1;

        ANSELB = 0x8000;
   
    AD1CON1 = 0x00E0;   // auto convert after end of sampling
    AD1CSSL = 0;        // no scanning required
    AD1CON3 = 0x1F02;   // system clock,max sample time = 31Tad, Tad = 2 x Tcy = 125ns >75ns
    AD1CON2 = 0;        // use MUXA, AVss and AVdd are used as Vref+/-
    AD1CON1bits.ADON = 1; // turn on the ADC
} //initADC
int readADC( int ANpin)
{

           AD1CHS  = ANpin;            // select analog input channel based upon I/o epxansion pin

    AD1CON1bits.SAMP = 1;       // start sampling, automatic conversion will follow
    while (!AD1CON1bits.DONE);   // wait to complete the conversion
    return ADC1BUF0;            // read the conversion result
} // readADC




void binary_to_ASCIIconvert( int n) {
bcd10000 =0x00;
bcd1000=0x00;
bcd100 =0x00;
bcdtens =0x00;
bcdunits =0x00;
while (n>=10000) {
n = n-10000;
bcd10000 =bcd10000+1;
}
while (n>=1000) {
n = n-1000;
bcd1000 =bcd1000+1;
}
while (n>=100) {
n = n-100;
bcd100 =bcd100+1;
}
while (n>=10) {
n = n-10;
bcdtens = bcdtens+1;
}

bcdunits = n;
bcd10000 =bcd10000+0x30;
bcd1000 =bcd1000+0x30;
bcd100 =bcd100+0x30;
bcdtens =bcdtens+0x30;
bcdunits =bcdunits+0x30;
}
//performs running average
int averagevalue (int ANpin) {
	int pin = ANpin;
	average =0;
	average = readADC(pin);
	average = average +readADC(pin);
	average = average +readADC(pin);
	average = average +readADC(pin);
	average = average/4;
	return average;


}

int DemoADC(int pin) {
	degree =0;
	int i =0;
	adcvalue = readADC(pin);    //select input channel
    binary_to_ASCIIconvert(adcvalue);
  	count[0]=bcd1000; //adc count
   	count[1]=bcd100;
   	count[2]=bcdtens;
   	count[3]=bcdunits;
   	degree =0;
   	for( i =0; i<adcvalue; i++) //calculates voltage from count ( assume .2 mv per count)
   	{  
        degree = degree + 0.35190616;   
    }
    return (int)degree;
//    binary_to_ASCIIconvert((int)degree);
//    count[5]=bcd100;
//    count[6]=bcdtens;
//    count[7]=bcdunits;
//    
//    LCD_Set_Cursor(1,1);
//    write_array_LCD(count, sizeof count);	
}

