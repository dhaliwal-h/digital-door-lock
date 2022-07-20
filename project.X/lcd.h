#ifndef _lcd
#define _lcd
//**********Nuts and Volts Library calls ********
#define row1    0
#define row2	16
#define row3	32
void LCD_Initialize(void);
void position_cursor( int position);
void clear_display(void);
void write_character_LCD( char mychar);
void write_string_LCD( char* chpointer);
void write_array_LCD( char* chpointer,int numofchar);

//************************************************
void LCDInit(void);

void move_FirstLine(void);
void move_SecondLine(void);
void move_ThirdLine(void);
void move_FourthLine(void);
void LCDWrite(int LCDData, int RSValue);
void initLCDIo(void);
void update_Display(char*chpointer, int numofchar);
void write_char(char*chpointer);
#endif
