#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <plib.h>
#include "system.h"
#include "lcd.h"
#include "delay.h"
#include "keypad.h"

#define led LATAbits.LATA0
#define   LATAbits.LATA3
#define LED1Tris TRISAbits.TRISA3

#define SYS_FREQ 		(8000000L) //8 Mhz internal fast oscillator
#define PB_DIV 1
#define PRESCALE1 256
#define TOGGLES_PER_SEC 1
#define T2_TICK (SYS_FREQ/PB_DIV/PRESCALE1/TOGGLES_PER_SEC)

volatile int u8_newKey = 0;

void __ISR(_CHANGE_NOTICE_VECTOR , ipl2) ChangeNotice_Handler(void) {
    u8_newKey = doKeyScan();
    // clear the interrupt flag
    IFS1bits.CNBIF=0;  //clear interrupt flag
}
void __ISR(_TIMER_2_VECTOR, ipl3) Timer2Handler (void) {
    mT2ClearIntFlag();
    led = ~led;
    Delayms(300);
} 

int compareArrays(char* a, char* b) {
  int ii;
  for(ii = 1; ii <= 4; ii++) {
    if (*a != *b) {
        return 0;
    }
    a++;
    b++;
    // better:
    // if(fabs(a[ii]-b[ii]) < 1e-10 * (fabs(a[ii]) + fabs(b[ii]))) {
    // with the appropriate tolerance
  }
  return 1;
}
int main (void){
    ANSELA = 0;
    ANSELB = 0;
    LATA = 0;
    TRISA = 0;
    LATB = 0;
    TRISB = 0;
    LATAbits.LATA0 = 0;
    TRISAbits.TRISA0 = 0;
    LED1 = 0;
    LED1Tris = 0;
    configKeypad();          //initialize the keypad
    
    int sequence = 0;
    //  enable multi-vector interrupts
     //set up timer 2 for interrupts
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_256, T2_TICK);
    INTEnableSystemMultiVectoredInt();
    ConfigIntTimer2(T23_INT_ON | T23_INT_PRIOR_3);
   //mT2ClearIntFlag();
    //1. clears CN interrupt flag
    //2. sets CN interrupt priority
    //3. enables CN interrupt
    IFS1bits.CNBIF=0;  //clear interrupt flag
    mT2ClearIntFlag();
    IPC8bits.CNIP =2;  //set interrupt priority to 2
    mT2SetIntPriority(3);
    IEC1bits.CNBIE=1;   //enable interrupts
    mT2IntEnable(1);
    Delayms(2000);
    LCD_Initialize();			//LCD initialize
    char password[4]= {'0','5','7','3'};
    char user_input[4] = {' ',' ',' ',' '};
    while (1)
    {
        if (u8_newKey)
        {
            if(u8_newKey == '1')
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '1';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '2') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '2';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '3') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '3';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '4') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '4';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '5') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '5';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '6') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '6';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '7') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '7';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '8') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '8';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '9') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '9';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '*') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '*';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '0') 
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '0';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            else if(u8_newKey == '#')
            {
                clear_display();
                LCD_Set_Cursor(1,1);
                user_input[sequence] = '#';
                write_array_LCD(user_input,4);
                sequence += 1;
            }
            
            if (sequence > 3) {
                Delayms(250);
                if ((compareArrays(password, user_input))){
                    clear_display();
                    LCD_Set_Cursor(1,1);
                    LED1 = 1;
                    write_string_LCD("Access Granted");
                }
                else {
                    clear_display();
                    LCD_Set_Cursor(1,1);
                    write_string_LCD("Access Denied");
                }
                int i =0;
                for (i = 0;i<4;i++)
                {
                    user_input[i] = ' ';
                }
                sequence = 0;
                Delayms(2000);
                LED1 = 0;
                clear_display();
            }
            u8_newKey = 0;
        }
    }
}










