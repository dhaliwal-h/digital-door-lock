//#include <plib.h>
#include "delay.h"
#include "lcd.h"


//IO port declaration and initialization for LCD.

#define E  LATBbits.LATB10
#define E_TRIS TRISBbits.TRISB10

#define RS  LATBbits.LATB2
#define RS_TRIS TRISBbits.TRISB2

#define LCD7 LATBbits.LATB15
#define LCD7_TRIS TRISBbits.TRISB15

#define LCD6 LATBbits.LATB14
#define LCD6_TRIS TRISBbits.TRISB14

#define LCD5 LATBbits.LATB13
#define LCD5_TRIS TRISBbits.TRISB13

#define LCD4 LATBbits.LATB11
#define LCD4_TRIS TRISBbits.TRISB11
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

int lcdport = 0;
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
void initLCDIo(void){ 
    ANSELA =0; //make sure analog is cleared
    ANSELB =0;
    //configure port A to drive for output
	
    LCD7 =0;
    LCD6 =0;
    LCD5 =0;
    LCD4 =0;
	
	LCD4_TRIS = 0;
	LCD5_TRIS = 0;
	LCD6_TRIS = 0;
	LCD7_TRIS = 0;


    //configure port b
	RS = 0;
	E = 0;
    RS_TRIS = 0;
    E_TRIS = 0;
}



//low level driver derived from Predko Evil Genius p 127
void LCDWrite(int LCDData, int RSValue){
	lcdport = (LCDData >> 4)&0x0f; //get high 4 bits for output
    if ((lcdport & 0x0008) !=0)
		LCD7 =1;
    else    
        LCD7 =0;
	if ((lcdport & 0x0004) !=0)
		LCD6 =1;
    else    
        LCD6 =0;
    if ((lcdport & 0x0002) !=0)
		LCD5 =1;
    else    
        LCD5 =0;
    if ((lcdport & 0x0001) !=0)
		LCD4 =1;
    else    
        LCD4 =0;
    //fix for 
	RS = RSValue;
	//toggle E
	E =0;
    delay_1us();
    E =1;
    delay_1us();
    E=0;
	lcdport = LCDData &0x0f; //get low 4 bits for output
	//fix for RB2 versus RA2
    if ((lcdport & 0x0008) !=0)
		LCD7 =1;
    else    
        LCD7 =0;
	if ((lcdport & 0x0004) !=0)
		LCD6 =1;
    else    
        LCD6 =0;
    if ((lcdport & 0x0002) !=0)
		LCD5 =1;
    else    
        LCD5 =0;
    if ((lcdport & 0x0001) !=0)
		LCD4 =1;
    else    
        LCD4 =0;
	RS =RSValue;
	//toggle E
		E=0;
		  delay_1us();
		E =1;
			delay_1us();
		E=0;

	Delayms(5);
}
void LCDInit() {
    int i =0; 
    //start with everything low
    LCD7 = 0;
    LCD6 = 0;
    LCD5 = 0;
    LCD4 = 0;
    //power up wait
	Delayms(40);
    //start initialization process
    LCD7 = 0;
    LCD6 = 0;
    LCD5 = 1;
    LCD4 = 1;
	E=0;
	delay_1us();
	E=1;
	 delay_1us();
	E=0;		//send reset1 command 03
    Delayms(5);
	E=0 ;
	 delay_1us();
	E=1;
	 delay_1us();
	E=0;		//repeat reset2 command 03
	Delay10us(3);
 	E=0;
 	 delay_1us();
	E=1;
	 delay_1us();
	E=0;		//send reset3 command third time 03
    Delay10us(3);
	
    //initialize 4 LCD 4 bit mode 02
    LCD7 = 0;
    LCD6 = 0;
    LCD5 = 1;
    LCD4 = 0;
    
	E=0;
 	delay_1us();
	E=1;
	 delay_1us();
	E=0;
	Delay10us(3);
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
//	LCD_Set_Cursor(1,1);
//	for ( i=0; TopMessage[i] !=0; i++){
//        LCDWrite(TopMessage[i],1);
//    }
//	LCD_Set_Cursor(2,1);
//    for ( i=0; SecMessage[i] !=0; i++){
//        LCDWrite(SecMessage[i],1);
//    }
//    Delayms(1000);
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