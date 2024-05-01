
/*
 * pic18f442.c - 18F442 Device Library Source
 *
 * This file is part of the GNU PIC Library.
 *
 * January, 2004
 * The GNU PIC Library is maintained by,
 * 	Vangelis Rokas <vrokas@otenet.gr>
 *
 * $Id: pic18f442.c,v 1.1 2004/01/12 22:10:38 vrokas Exp $
 *
 */

#include <pic18f442.h>

sfr at 0xfff TOSU;
sfr at 0xffe TOSH;
sfr at 0xffd TOSL;
sfr at 0xffc STKPTR;
sfr at 0xffb PCLATU;
sfr at 0xffa PCLATH;
sfr at 0xff9 PCL;
sfr at 0xff8 TBLPTRU;
sfr at 0xff7 TBLPTRH;
sfr at 0xff6 TBLPTRL;
sfr at 0xff5 TABLAT;
sfr at 0xff4 PRODH;
sfr at 0xff3 PRODL;
sfr at 0xff2 INTCON;
sfr at 0xfef INDF0;
sfr at 0xfee POSTINC0;
sfr at 0xfed POSTDEC0;
sfr at 0xfec PREINC0;
sfr at 0xfeb PLUSW0;
sfr at 0xfea FSR0H;
sfr at 0xfe9 FSR0L;
sfr at 0xfe8 WREG;
sfr at 0xfe7 INDF1;
sfr at 0xfe6 POSTINC1;
sfr at 0xfe5 POSTDEC1;
sfr at 0xfe4 PREINC1;
sfr at 0xfe3 PLUSW1;
sfr at 0xfe2 FSR1H;
sfr at 0xfe1 FSR1L;
sfr at 0xfe0 BSR;
sfr at 0xfdf INDF2;
sfr at 0xfde POSTINC2;
sfr at 0xfdd POSTDEC2;
sfr at 0xfdc PREINC2;
sfr at 0xfdb PLUSW2;
sfr at 0xfda FSR2H;
sfr at 0xfd9 FSR2L;
sfr at 0xfd8 STATUS;
sfr at 0xfd3 OSCCON;
sfr at 0xfd2 LVDCON;
sfr at 0xfd1 WDTCON;
sfr at 0xfd0 RCON;
sfr at 0xf9f IPR1;
sfr at 0xf9e PIR1;
sfr at 0xf9d PIE1;
sfr at 0xff1 INTCON2;
sfr at 0xff0 INTCON3;
sfr at 0xfa2 IPR2;
sfr at 0xfa1 PIR2;
sfr at 0xfa0 PIE2;
sfr at 0xf80 PORTA;
sfr at 0xf89 LATA;
sfr at 0xf92 TRISA;
sfr at 0xf81 PORTB;
sfr at 0xf93 TRISB;
sfr at 0xf8a LATB;
sfr at 0xf82 PORTC;
sfr at 0xf8b LATC;
sfr at 0xf94 TRISC;
sfr at 0xf83 PORTD;
sfr at 0xf8c LATD;
sfr at 0xf95 TRISD;
sfr at 0xf84 PORTE;
sfr at 0xf8d LATE;
sfr at 0xf96 TRISE;
sfr at 0xfc4 ADRESH;
sfr at 0xfc3 ADRESL;
sfr at 0xfc2 ADCON0;
sfr at 0xfc1 ADCON1;
sfr at 0xfbf CCPR1H;
sfr at 0xfbe CCPR1L;
sfr at 0xfbd CCP1CON;
sfr at 0xfbc CCPR2H;
sfr at 0xfbb CCPR2L;
sfr at 0xfba CCP2CON;
sfr at 0xfa9 EEADR;
sfr at 0xfa8 EEDATA;
sfr at 0xfa7 EECON2;
sfr at 0xfa6 EECON1;
sfr at 0xfc9 SSPBUF;
sfr at 0xfc8 SSPADD;
sfr at 0xfc7 SSPSTAT;
sfr at 0xfc6 SSPCON1;
sfr at 0xfc5 SSPCON2;
sfr at 0xfd7 TMR0H;
sfr at 0xfd6 TMR0L;
sfr at 0xfd5 T0CON;
sfr at 0xfcf TMR1H;
sfr at 0xfce TMR1L;
sfr at 0xfcd T1CON;
sfr at 0xfcc TMR2;
sfr at 0xfcb PR2;
sfr at 0xfca T2CON;
sfr at 0xfb3 TMR3H;
sfr at 0xfb2 TMR3L;
sfr at 0xfb1 T3CON;
sfr at 0xfaf SPBRG;
sfr at 0xfae RCREG;
sfr at 0xfad TXREG;
sfr at 0xfac TXSTA;
sfr at 0xfab RCSTA;


