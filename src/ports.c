/*==============================================================
    Ports.c - Contains ports declerations for I/O  
  ECE 306 - Homework 3
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/
#include "macros.h"
#include "msp430.h"
#include "functions.h"

  
void Init_Port1(void){
// Configure Port 1 -------------------------------------------------------------
// V_DETECT_R (0x01) // Voltage from Right Detector
// V_DETECT_L (0x02) // Voltage from Right Detector
// LCD_BACKLITE(0x04) // Control Signal for LCD_BACKLITE
// V_THUMB (0x08) // Voltage from Thumb Wheel
// SPI_CS_LCD (0x10) // LCD Chip Select
// RESET_LCD (0x20) // LCD Reset
// SIMO_B (0x40) // SPI mode - slave in/master out of USCI_B0
// SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0
//------------------------------------------------------------------------------
P1SEL0 = CLEAR; // P1 set as I/0
P1SEL1 = CLEAR; // P1 set as I/0
P1DIR = CLEAR; // Set P1 direction to input
  
P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
P1SEL1 |= V_DETECT_R; // V_DETECT_R selected
P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
P1SEL1 |= V_DETECT_L; // V_DETECT_L selected

P1SEL0 &=~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
P1SEL1 &=~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
P1OUT |= LCD_BACKLITE; // LCD_BACKLITE Port Pin set high
P1DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output

P1SEL0 |= V_THUMB; // V_THUMB selected
P1SEL1 |= V_THUMB; // V_THUMB selected

P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
P1OUT |= SPI_CS_LCD; // SPI_CS_LCD Port Pin set high
P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction

P1SEL0 &= ~RESET_LCD; // RESET_LCD GPI/O selected
P1SEL1 &= ~ RESET_LCD; // RESET_LCD GPI/O selected
P1OUT &= ~ RESET_LCD; // RESET_LCD Port Pin set low
P1DIR |= RESET_LCD; // Set RESET_LCD output direction

P1SEL0 &= ~SIMO_B; // SIMO_B selected
P1SEL1 |= SIMO_B; // SIMO_B selected
P1DIR |= SIMO_B; // SIMO_B set to Output

P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
P1OUT |= SOMI_B; // SOMI_B Port Pin set for Pull-up
P1DIR &= ~SOMI_B; // SOMI_B set to Input
P1REN |= SOMI_B; // Enable pullup resistor
//------------------------------------------------------------------------------
}
void Init_Port2(void){
  // Configure Port 2 -------------------------------------------------------------
/* 
  Parameters: None
  Return: None
  

  Definitions:  
  USB_TXD (0x01) // GP I/O with portd interupt and wake up, 
                        Transmit data - Slave in, master out
 USB_RXD (0x02) // GP I/O with with interupt and wake up
                    Receive data - Save out, master in
 SPI_SCK (0x04) // GP I/O with interupt and wake up
                      Clock signal input
 UNKNOWN1 (0x08) //
 UNKNOWN2 (0x10) // 
 CPU_TXD (0x20) //  
 CPU_RXD (0x40) // 
 UNKNOWN3 (0x80) // 
*/
 //------------------------------------------------------------------------------
P2SEL0 = CLEAR; // P2 set as I/0
P2SEL1 = CLEAR; // P2 set as I/0
P2DIR = CLEAR; // Set P2 direction to input
  
P2SEL0 &= ~USB_TXD; //
P2SEL1 |= USB_TXD;
P2OUT &= ~USB_TXD;
P2DIR |= USB_TXD; //Set pin 1 to transmit usb data

P2SEL0 |= USB_RXD; //
P2SEL1 &= ~USB_RXD;
P2OUT &= ~USB_RXD;
P2DIR &= ~USB_RXD;  //set pin 2 to receive usb data
P2REN &= ~USB_RXD; // Disable pullup resistor

P2SEL0 &= ~SPI_SCK; 
P2SEL1 |= SPI_SCK;
P2OUT |= SPI_SCK;
P2DIR |= SPI_SCK;

P2SEL0 &= ~UNKNOWN1; 
P2SEL1 &= ~UNKNOWN1;
P2OUT &= ~UNKNOWN1;
P2DIR &= ~UNKNOWN1;
P2REN &= ~UNKNOWN1;

P2SEL0 &= ~UNKNOWN2;
P2SEL1 &= ~UNKNOWN2;
P2OUT &= ~UNKNOWN2;
P2DIR &= ~UNKNOWN2;
P2REN &= ~UNKNOWN2;

//TRANMIT CPU DATA
P2SEL0 &= ~CPU_TXD;
P2SEL1 |= CPU_TXD;
P2OUT &=~CPU_TXD;
P2DIR |= CPU_TXD;
// RECEIVE CPU DATA
P2SEL0 &= ~CPU_RXD;
P2SEL1 |= CPU_RXD;
P2OUT &= ~CPU_RXD;
P2DIR &= ~CPU_RXD;

P2SEL0 &= ~UNKNOWN3;
P2SEL1 &= ~UNKNOWN3;
P2OUT &= ~UNKNOWN3;
P2DIR &= ~UNKNOWN3;
P2REN &= ~UNKNOWN3;
}
// Port 3
void Init_Port3(void){
 /* 
  Parameters: None
  Return: None 
 
 X1 (0x01) // 
 Y1 (0x02) // 
 Z1 (0x04) // 
 IR_LED (0x08) // IR LED used for detecting the course line
 R_FORWARD (0x10) // Output for right motor -> forward
 L_FORWARD (0x20) // Output for left motor -> forward 
 R_REVERSE (0x40) // Output for right motor -> Reverse
 L_REVERSE (0x80) // Output for left motor -> Reverse
  
  
  */ 
P3SEL0 = CLEAR; // 
P3SEL1 = CLEAR; // 
P3DIR = CLEAR; //  
  
P3SEL0 = CLEAR; // P1 set as I/0
P3SEL1 = CLEAR; // P1 set as I/0
P3DIR = CLEAR; // Set P1 direction to input

P3SEL0 &= ~X1;
P3SEL1 &= ~X1;
P3OUT &= ~X1;
P3DIR &= ~X1;   //SET AS INPUT
P3REN &= ~X1;

P3SEL0 &= ~Y1;
P3SEL1 &= ~Y1;
P3OUT &= ~Y1;
P3DIR &= ~Y1; //SET AS INTPUT
P3REN &= ~Y1;

P3SEL0 &= ~Z1;
P3SEL1 &= ~Z1;
P3OUT &= ~Z1; 
P3DIR &= ~Z1; //SET AS INPUT
P3REN &= ~Z1; 

P3SEL0 &= ~IR_LED;
P3SEL1 &= ~IR_LED;
P3OUT &= ~IR_LED;
P3DIR |= IR_LED; //SET AS OUTPUT
//Set Right Forward pin
P3SEL0 |= R_FORWARD;
P3SEL1 &= ~R_FORWARD;
P3DIR |= R_FORWARD; //Set as OUTPUT

// Set Left motor forwared pin
P3SEL0 |= L_FORWARD;  
P3SEL1 &= ~L_FORWARD;
P3DIR |= L_FORWARD; //SET AS OUTPUT

// Set Right reverse pin
P3SEL0 |= R_REVERSE;
P3SEL1 &= ~R_REVERSE;
P3DIR |= R_REVERSE; //SET AS OUTPUT
// Set Left Reverse
P3SEL0 |= L_REVERSE; // SEL 0 and 1 are Low
P3SEL1 &= ~L_REVERSE;
P3DIR |= L_REVERSE; //SET AS OUTPUT
}
void Init_Port4(void){
 /* 
  Parameters: None
  Return: None 
 
 SW1 (0x01) // Button 1
 SW2 (0x02) // Button 2
  
  */  
  
P4SEL0 &= ~SW1; //SEL0 
P4SEL1 &= ~SW1;
P4OUT |= SW1; //OUT VALUE IS 1
P4DIR &= ~SW1; //SET AS INPUT
P4REN |= SW1; //ENABLE PULLUP RESISTOR
P4IES |= SW1; // SW1 Hi/Lo edge interrupt
P4IFG &= ~SW1; // IFG SW1 cleared
P4IE |= SW1; // SW1 interrupt Enabled


P4SEL0 &= ~SW2; //SEL0 
P4SEL1 &= ~SW2;  //
P4OUT |= SW2; //OUT VALUE IS 1
P4DIR &= ~SW2; //SET AS INPUT
P4REN |= SW2; //ENABLE PULLUP RESISTOR
P4IES |= SW2; // SW2 Hi/Lo edge interrupt
P4IFG &= ~SW2; // IFG SW2 cleared
P4IE |= SW2; // SW2 interrupt enabled


}

void Init_PortJ(int j_pins){
  
  /*
  Parameters: None
  Return: None
  
  
  */
  PJSEL0 = CLEAR; //CLEAR = 0x00
  PJSEL1 = CLEAR;
  PJDIR = CLEAR;
    
  //if(j_pins == USE_IOT_WAKEUP){  
  // Port PJ.0
  PJSEL0 &= ~IOT_WAKEUP; 
  PJSEL1 &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_WAKEUP;
  PJDIR |= IOT_WAKEUP;
  //}
 /* else{
  PJSEL0 |= IOT_WAKEUP; 
  PJSEL1 &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_WAKEUP;
  PJDIR |= IOT_WAKEUP;
  }
 */ 
  // Port PJ.1
  PJSEL0 &= ~IOT_FACTORY; 
  PJSEL1 &= ~IOT_FACTORY;
  PJOUT &= ~IOT_FACTORY;
  PJDIR |= IOT_FACTORY;
  // Port PJ.2
  PJSEL0 &= ~IOT_STA_MINIAP; 
  PJSEL1 &= ~IOT_STA_MINIAP;
  PJOUT |= IOT_STA_MINIAP; //
  PJDIR |= IOT_STA_MINIAP;
  // Port PJ.3
  PJSEL0 &= ~IOT_RESET; 
  PJSEL1 &= ~IOT_RESET;
  PJOUT &= ~IOT_RESET;
  PJDIR |= IOT_RESET;
  
}







