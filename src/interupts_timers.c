/*================================================================
    intterupts_timers.c  
  ECE 306 - Homework 6
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/

#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern int count;
extern int Stop;
extern unsigned int Go;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int Time_Sequence;
extern unsigned int display_flag_left;
extern unsigned int display_flag_right;
extern unsigned int display_flag_thumb;
extern unsigned int wait_time;
extern unsigned int time_interval;
extern volatile unsigned int drive_time;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerA0_0(void){
  TA0CCR0 += TA0CCR0_INTERVAL; //2500 interveral -> 
  display_flag_left++;
  display_flag_right++;
  display_flag_thumb++;
  time_interval++;
  
}



   






