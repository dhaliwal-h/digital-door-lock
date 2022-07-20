#include <p32xxxx.h>
#include "keypad.h"


#define C0 _RB5
#define C1 _RB7
#define C2 _RB8
#define C3 _RB9
int i;

void CONFIG_COLUMN(void) {
    TRISBbits.TRISB7 = 1;
    CNPUBbits.CNPUB7 = 1;
    CNENBbits.CNIEB7 =1;  //change notice enable
    CNCONBbits.ON =1;  //change notice control
    
    TRISBbits.TRISB5 = 1;
    CNPUBbits.CNPUB5 = 1;
    CNENBbits.CNIEB5 =1;  //change notice enable
    CNCONBbits.ON =1;  //change notice control
    
    TRISBbits.TRISB9 = 1;
    CNPUBbits.CNPUB9 = 1;
    CNENBbits.CNIEB9 =1;  //change notice enable
    CNCONBbits.ON =1;  //change notice control
    
    TRISBbits.TRISB8 = 1;
    CNPUBbits.CNPUB8 = 1;
    CNENBbits.CNIEB8 =1;  //change notice enable
    CNCONBbits.ON =1;  //change notice control
}

#define R0 _LATA2
#define R1 _LATB3
#define R2 _LATB0

void CONFIG_ROW(void) {
  TRISAbits.TRISA2 = 0;
  TRISBbits.TRISB3 = 0;
  TRISBbits.TRISB0 = 0;
}
static inline void DRIVE_ROW_LOW() {
  R0 = 0;
  R1 = 0;
  R2 = 0;
}
static inline void DRIVE_ROW_HIGH() {
  R0 = 1;
  R1 = 1;
  R2 = 1;
}
void configKeypad(void) {
  CONFIG_ROW();
  DRIVE_ROW_LOW();
  CONFIG_COLUMN();
  delay_1us();     //wait for pullups to stabilize inputs
}
//drive one row low
void setOneRowLow(int u8_x) {
  switch (u8_x) {
    case 0:
      R0 = 0;
      R1 = 1;
      R2 = 1;
      break;
    case 1:
      R0 = 1;
      R1 = 0;
      R2 = 1;
      break;
    default:
      R0 = 1;
      R1 = 1;
      R2 = 0;
      break;
  }
}
#define NUM_ROWS 3
#define NUM_COLS 4
const int au8_keyTable[NUM_ROWS][NUM_COLS] ={
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'}
};
#define KEY_PRESSED() (!C0 || !C1 || !C2 || !C3)   //any low
#define KEY_RELEASED() (C0 && C1 && C2 && C3)  //all high
int doKeyScan(void) {
  int u8_row, u8_col;
  //determine column
  if (!C0) u8_col = 0;
  else if (!C1) u8_col = 1;
  else if (!C2) u8_col = 2;
  else if (!C3) u8_col = 3;
  else return('E'); //error
  //determine row
  for (u8_row = 0; u8_row < NUM_ROWS; u8_row++) {
    setOneRowLow(u8_row); //enable one row low
    if (KEY_PRESSED()) {
        DRIVE_ROW_LOW(); //return rows to driving low
        return(au8_keyTable[u8_row][u8_col]);
    }
  }
  DRIVE_ROW_LOW(); //return rows to driving low
  return('E'); //error
}
void dokeycheck(void){
    int i;
    if(KEY_PRESSED() && doKeyScan() == '1'){
        i = 1;
    }
    if(KEY_PRESSED() && doKeyScan() == '2'){
        i = 2;
    }
    if(KEY_PRESSED() && doKeyScan() == '3'){
        i = 3;
    }
    if(KEY_PRESSED() && doKeyScan() == '4'){
        i = 4;
    }
    if(KEY_PRESSED() && doKeyScan() == '5'){
        i = 5;
    }
    if(KEY_PRESSED() && doKeyScan() == '6'){
        i = 6;
    }
    if(KEY_PRESSED() && doKeyScan() == '7'){
        i = 7;
    }
    if(KEY_PRESSED() && doKeyScan() == '8'){
        i = 8;
    }
    if(KEY_PRESSED() && doKeyScan() == '9'){
        i = 9;
    }
    if(KEY_PRESSED() && doKeyScan() == '0'){
        i = 0;
    }
}