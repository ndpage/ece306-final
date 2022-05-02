/*================================================================
    intterupts_ports.c  
  ECE 306 - Homework 6
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/
#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern int count;
extern volatile unsigned int SW1_pressed;
extern volatile unsigned int SW2_pressed;
extern volatile unsigned int SW1_debounce;
extern volatile unsigned int SW2_debounce;
extern volatile unsigned int SW1_count;
extern volatile unsigned int SW2_count;
extern char *display_4;
extern char *display_3;
extern char *display_2;
extern char *display_1;
extern char *posL4;
extern char big;

extern unsigned int Go;

extern unsigned int ADC_Right_Detector;
extern unsigned int ADC_Left_Detector;
extern unsigned int ADC_Thumb;
extern unsigned int Left_White;
extern unsigned int Right_White;
extern unsigned int Left_Black;
extern unsigned int Right_Black;

unsigned int calibrate;
extern unsigned int wait_time;
// Interrupt -- Turns on and off backlite, sets appropriate flags, and updates timer control registers 
#pragma vector=PORT4_VECTOR

__interrupt void switch_interrupt(void){
// Switch 1-------------------------------------------
  if (P4IFG & SW1) {
  P4IFG &= ~SW1; // disable SW1 flag bit  
  SW1_pressed = ACTIVATED; //Set SW1 flag variable 
  P4IE &= ~SW1; // SW1 interrupt disabled
 // P3OUT |= IR_LED; // Turn on the IR LED
 
  
  //display_1="Reset IOT ";
  //PJOUT &= ~IOT_RESET;  
   
  TA0CCR1 = TA0R + TA0_REG_INTERVAL; // update control reg 1
   TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR2
  TA0CCTL1 |= CCIE;
  
  }
  // Switch 2 ------------------------------------------
  // Turns on backlite when SW2 is pressed
  if (P4IFG & SW2) {
  SW2_pressed = ACTIVATED; // Set SW2 flag variable
  P4IE &= ~SW2; // SW2 interrupt disabled  

  TA0CCR2 = TA0R + TA0_REG_INTERVAL; // update control reg 2
  TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
  TA0CCTL2 |= CCIE;
 
  }

}
 
//-----------------------------------------------------------------

// Determines whether control reg 1 or 2 is being used 

 #pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){

switch(__even_in_range(TA0IV,OVERFLOW)){
case INTERRUPT: break; // No interrupt
case SWITCH_1: // CCR1 not used
     TA0CCTL1 &= ~CCIE;  // Reset control register
     SW1_pressed = CLEAR;  // Reset SW1 flag variable
     SW1_count++;
     P4IE |= SW1; // enable SW1 interrupt 
//TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
break;
case SWITCH_2: // CCR2 not used
    
    TA0CCTL2 &= ~CCIE;  // Reset control register 
    P4IE |= SW2; // enable SW2 interrupt 
    SW2_pressed = CLEAR; // Reset SW2 flag variable   
    P4IFG &= ~SW2;

break;
case OVERFLOW: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break;
}
 //-------------------------------------------------------------------

}






