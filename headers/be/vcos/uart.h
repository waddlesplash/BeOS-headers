/*name and version number:@(#)iouart_d.h	5.1*/
/*date of get: 		  4/21/93 09:00:58*/
/*date of delta:	  4/21/93 08:55:28*/
/****************************************************************
File :	iouart_d.h
Description :
	Contains the declarations for the UART layer functions.

Revision History :
	Initials	Date		Change
	VR      	10/22/92	Initial
*****************************************************************/

#define byte unsigned char
#define word unsigned
#define dword unsigned long

extern int  UART_init ( void ) ;
extern void UART_reset ( void ) ;
extern void UART_background ( void ) ;

#define UART_CD_ON       		0x0001
#define UART_DSR_ON       		0x0002
#define UART_RING_ON      		0x0004
#define UART_CTS_ON       		0x0008
#define UART_DTE_RX_ON   		0x0010
#define UART_DTE_TX_ON   		0x0020
#define UART_DCE_BREAK_ON		0x0040
#define UART_DTR_ON      		0x0100
#define UART_RTS_ON      		0x0200
#define UART_DTE_BREAK_ON		0x0400
extern word UART_get_status ( void ) ;

extern void UART_dtr_off ( void ) ;
extern void UART_dtr_on ( void ) ;
extern void UART_rts_off ( void ) ;
extern void UART_rts_on ( void ) ;
extern void UART_start_break ( void ) ;
extern void UART_stop_break ( void ) ;
extern void UART_data_bits ( byte data_bits ) ;
extern void UART_stop_bits ( byte stop_bits ) ;
extern void UART_parity ( byte parity ) ;
extern word UART_CommWriteString ( byte *lpstring, word count ) ;
extern word UART_CommWriteCount ( void ) ;
extern word UART_CommReadString ( byte *lpstring, word count ) ;
extern word UART_CommReadCount ( void ) ;
extern void UART_SetQue ( byte *pqTx, word cbqTx, byte *pqRx, word cbqRx ) ;
extern void UART_Flush ( int queue ) ;
extern void UART_timer ( void ) ;

