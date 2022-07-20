#ifndef __ADCDRV_H__
#define __ADCDRV_H__


//revision thk 11/25/09 N+V simplified library
// expansion bus pin to ADC channel number
//for PIC32MX 2/12/2012 thk
//only pins AN9,AN10, AN11 can support analog ADC in channels are supported
extern char bcd10000;
extern char bcd1000;
extern char bcd100;
extern char bcdtens;
extern char bcdunits;
#define AN9 	0x00090000 // AN9 left photocell
#define AN10 	0x000A0000 // AN10 Right photocell
#define AN11    0x000B0000 // AN11 Right photocell




int readADC( int ANpin);   //parameter I/O expansion pin number this function does conversion
void initADC( int ANpin);	//initialize ADC operation ofr this I/O pin

void binary_to_ASCIIconvert( int n);
int averagevalue (int ANpin);

#endif




