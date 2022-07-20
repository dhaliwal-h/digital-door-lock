
#include <plib.h>
#include "delay.h"
#include "lcd.h"

#define LCDPORT LATA
#define E  LATBbits.LATB11
#define RS  LATBbits.LATB10
#define LCDPORT7 
#define LCDPORT6
#define LCDPORT5
#define LCDPORT4

//EA DOG M Instructions 4 bit 3.3V
//modification for two line

#define FUNCT1 		0x29	//DL-4bits 2 lines Table select =1
#define BIAS 		0x15	// BIAS 1:5 3 line LCD
//#define BIAS 		0x14	// BIAS 1:5 2 line LCD
#define PWRCNTRL	0x55	//booster on  constrast c5 ,set c4
#define FOLLOW		0x6D	//set booster follower and gain
#define CONST		0x78	// set constrast c3,c2,c1
#define FUNCT2		0x28	//switch back to table =0
#define DISPLAY     0x0E	//display on/off --display on, cursor off, cursor blink off
#define CLEAR		0x01	//delete display --cursor at home
#define ENTRY		0x06	//cursor auto-increment




const char TopMessage[]=    "PIC3MX220F032B ";
const char SecMessage[]=    " LCD Test";


//************************************************************************
///Simple library calls
//modified for PIC32MX220F032B microstick II 2/10/2012

//*************************************************************************
void LCD_Initialize(void) {  //one call initialize for LCD

	initLCDIo();	//initializes PIC24F I/O
	LCDInit();		//initializes EADOG 16x3

}

void position_cursor( int position) { // position 0-47

	int address = position+ 0x80;
		LCDWrite(address,0); //move curror to display


}

void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1) 
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCDWrite(Temp,0); //move curror to display
    //writeLCD(High4,0,0,1);
    //writeLCD(Low4,0,0,1);
  }
  if(r == 2) 
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCDWrite(Temp,0); //move curror to display
    //writeLCD(High4,0,0,1);
    //writeLCD(Low4,0,0,1);
  }
}

void write_character_LCD( char mychar) {
		char * pt;       //need to make a pointer
		pt = &mychar;
		update_Display( pt,1);  //display single character using pt and numofchar =1

}

void write_string_LCD( char* chpointer) {


while (*chpointer != '\0')
 {
	LCDWrite(*chpointer,1);
	chpointer++;

}

}

void write_array_LCD( char* chpointer, int numofchar ) {

	int i=0;
	//LCDWrite(0b00000001,0); //Clear LCD

	for (i =0; i<numofchar; i++) {
	LCDWrite(*chpointer,1);
	chpointer++;

}

}


/*=============================================================================
I/O INITIALISATION ROUTINE
=============================================================================*/
void initLCDIo(void)
{ ANSELA =0; //make sure analog is cleared
     ANSELB =0;
//configure port A to drive for output
	LATAbits.LATA0 =0;
	LATAbits.LATA1 =0;
	LATAbits.LATA2 =0; //because of CLKI don't use
	LATBbits.LATB2 =0;	// use RB2 instead
	LATAbits.LATA3 =0;
	TRISAbits.TRISA0=0;
	TRISAbits.TRISA1=0;
	TRISAbits.TRISA2=1; //use RB2 instead of A2
	TRISBbits.TRISB2 =0;
	TRISAbits.TRISA3=0;


//configure port b
	LATBbits.LATB10 =0;
	LATBbits.LATB11=0;
	TRISBbits.TRISB10 =0;
	TRISBbits.TRISB11 =0;;

}



//low level driver derived from Predko Evil Genius p 127
void LCDWrite(int LCDData, int RSValue){
	LCDPORT = (LCDData >> 4)&0x0f; //get high 4 bits for output
	//fix for RB2 versus RA2
	if ((LCDPORT & 0x0004) !=0)
		LATBbits.LATB2 =1;
    else    
        LATBbits.LATB2 =0;
	RS = RSValue;
	//toggle E
	    E =0;
	    delay_1us();
		E =1;
		delay_1us();
		E=0;
	LCDPORT = LCDData &0x0f; //get low 4 bits for output
	//fix for RB2 versus RA2
	if ((LCDPORT & 0x0004)!=0)
		LATBbits.LATB2 =1;
		else
	LATBbits.LATB2 =0;
	RS =RSValue;
	//toggle E
		E=0;
		  delay_1us();
		E =1;
			delay_1us();
		E=0;

	delay_5msec();
}
void LCDInit() {
	int i =0;
	//fix for RB2
	LATBbits.LATB2 =0;
LCDPORT =0; //start with everything low
//power up wait
	delay_40msec();
		//fix for RB2
	LATBbits.LATB2 =0;
	LCDPORT = 3; //start initialization process
	E=0;
	 delay_1us();
	E=1;
	 delay_1us();
	E=0;		//send reset1 command 03
delay_5msec();
	E=0 ;
	 delay_1us();
	E=1;
	 delay_1us();
	E=0;		//repeat reset2 command 03
	delay_30us();

 	E=0;
 	 delay_1us();
	E=1;
	 delay_1us();
	E=0;		//send reset3 command third time 03
delay_30us();
	//fix for RB2
	LATBbits.LATB2 =0;
	LCDPORT =2 ; 	//initialize 4 LCD 4 bit mode 02
	E=0;
 	delay_1us();
	E=1;
	 delay_1us();
	E=0;
	delay_30us();
// FUNCT1 		0x29	//DL-4bits 2 lines Table select =1
LCDWrite(FUNCT1,0);
// BIAS 		0x14	// BIAS 1:5 2 line LCD
LCDWrite(BIAS,0);
// PWRCNTRL	0x55	//booster on  constrast c5 ,set c4
LCDWrite(PWRCNTRL,0);
// FOLLOW		0x6D	//set booster follower and gain
LCDWrite(FOLLOW,0);
// CONST		0x78	// set constrast c3,c2,c1
LCDWrite(CONST,0);
// FUNCT2		0x28	//switch back to table =0
LCDWrite(FUNCT2,0);
// DISPLAY     0x0F	//display on/off --display on, cursor on, cursor blink
LCDWrite(DISPLAY,0);
// CLEAR		0x01	//delete display --cursor at home
LCDWrite(CLEAR,0);
// ENTRY		0x06	//cursor auto-increment
LCDWrite(ENTRY,0);
LCDWrite(0x0C,0);


	move_FirstLine();
	for ( i=0; TopMessage[i] !=0; i++)
	LCDWrite(TopMessage[i],1);
	move_SecondLine();
for ( i=0; SecMessage[i] !=0; i++)
	LCDWrite(SecMessage[i],1);

}
void write_char(char*chpointer) {
		LCDWrite(*chpointer,1);

}
void update_Display(char*chpointer, int numofchar) {
int i=0;
	//LCDWrite(0b00000001,0); //Clear LCD

	for (i =0; i<numofchar; i++) {
	LCDWrite(*chpointer,1);
	chpointer++;

}

}
void clear_display() {
	LCDWrite(0b00000001,0); //clear LCD

}
void move_FirstLine() {
    unsigned char address =0x80+0x00; // line 1
	LCDWrite(address,0); //move curror to display
}
void move_SecondLine() {
  unsigned char address =0x80+16; // line 2--3 line idsplay
  //unsigned char address =0x80+0x40; // line 2 of 2 line
	LCDWrite(address,0); //move curror to display
}
void move_ThirdLine() {
  unsigned char address =0x80+32; // line 3
	LCDWrite(address,0); //move curror to display
}
void move_FourthLine() {
  unsigned char address =0x80+0x54; // line 4
	LCDWrite(address,0); //move curror to display
}



