/*
** CONIO.C
** Basic CONSOLE I/O for Microstick II UART 2 board
*/
#include <plib.h>
#include "conU2.h"
#define FPB 8000000
#define BAUDRATE 2400
#define BRGVAL ((FPB/BAUDRATE)/16)-1
#define U_ENABLE 0x8000		// enable the UART
#define U_TXRX	 0x1400		// enable transmission and reception
// init the serial port (UART2, 2400, 8, N, 1 )
void initU2( void)
{ 
	U2BRG = BRGVAL; // BAUD Rate Setting for 9600
	U2MODE 	= U_ENABLE;
	U2STA 	= U_TXRX;
	U2MODEbits.BRGH = 0; // standard mode
} // initCon

// send a character to the UART2 serial port
int putU2( int c)
{
	while ( U2STAbits.UTXBF);   // wait while Tx buffer full
	U2TXREG = c;
	return c;
} // putU2
// wait for a new character to arrive to the UART2 serial port -don't use during interrupts
char getU2( void)
{
  	while ( !U2STAbits.URXDA);	// wait for a new character to arrive
	return U2RXREG;		// read the character from the receive buffer
}// getU2
// send a null terminated string to the UART2 serial port
void putsU2( char *s)
{
	while( *s)			// loop until *s == '\0' the  end of the string
		putU2( *s++);	// send the character and point to the next one
    putU2( '\r');       // terminate with a cr / line feed
} // putsU2
char *getsn( char *s, int len)
{
    char *p = s;            // copy the buffer pointer 
    do{
        *s = getU2();       // wait for a new character
        putU2( *s);         // echo character
        
        if (( *s==BACKSPACE)&&( s>p))
        {
            putU2( ' ');     // overwrite the last character
            putU2( BACKSPACE);
            len++;
            s--;            // back the pointer
            continue;
        }
        if ( *s=='\n')      // line feed, ignore it
            continue;
        if ( *s=='\r')      // end of line, end loop
            break;          
        s++;                // increment buffer pointer
        len--;
    } while ( len>1 );      // until buffer full
 
    *s = '\0';              // null terminate the string 
    
    return p;               // return buffer pointer
} // getsn
    

