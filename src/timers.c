/*============================
    Timers.c - Contains timer functions
  ECE 306 - Homework 3
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==============================
*/
// Includes the timers function
#include "macros.h"
#include "msp430.h"
#include "functions.h"
extern volatile char one_time;
extern volatile char one_time;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int two_msec_count;

extern unsigned int right_forward_rate;
extern unsigned int left_forward_rate;
extern unsigned int right_reverse_rate;
extern unsigned int left_reverse_rate;

extern unsigned int time_interval;


void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
//  Init_Timer_A1(); //
//  Init_Timer_B0(); //
  Init_Timer_B1(); //
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Timer A0 initialization sets up both A0_0 and A0_1-A0_2
void Init_Timer_A0(void) {
TA0CTL = TASSEL__SMCLK; // SMCLK source
TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
TA0CTL |= MC__CONTINOUS; // Continuous up
TA0CTL |= ID__2; // Divide clock by 2
TA0CTL &= ~TAIE; // Disable Overflow Interrupt
TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag
TA0EX0 = TAIDEX_7; // Divide clock by an additional 8
TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
TA0CCTL0 |= CCIE; // CCR0 enable interrupt
// TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
// TA0CCTL1 |= CCIE; // CCR1 enable interrupt
// TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
// TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}
//------------------------------------------------------------------------------

/* Timer B1 is used for forward direction PWM*/
void Init_Timer_B1(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
//------------------------------------------------------------------------------
TB1CTL = TBSSEL__SMCLK; // SMCLK
TB1CTL |= MC_1; // Up Mode
TB1CTL |= TBCLR; // Clear TAR

right_forward_rate = OFF; // Set Right Forward Off
left_forward_rate = OFF; // Set Left Forward Off

TB1CCR0 = WHEEL_PERIOD; // PWM Period
TB1CCTL1 = OUTMOD_7; // CCR1 reset/set
TB1CCR1 = right_forward_rate; // P3.4 Right Forward PWM duty cycle
TB1CCTL2 = OUTMOD_7; // CCR2 reset/set
TB1CCR2 = left_forward_rate; // P3.5 Left Forward PWM duty cycle
//------------------------------------------------------------------------------
}
/* Timer B2 is used for Reverse direction PWM*/
void Init_Timer_B2(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
//------------------------------------------------------------------------------
TB2CTL = TBSSEL__SMCLK; // SMCLK
TB2CTL |= MC_1; // Up Mode
TB2CTL |= TBCLR; // Clear TAR

right_reverse_rate = OFF; // Set Right Forward Off
left_reverse_rate = OFF; // Set Left Forward Off

TB2CCR0 = WHEEL_PERIOD; // PWM Period
TB2CCTL1 = OUTMOD_7; // CCR1 reset/set
TB2CCR1 = OFF; // P3.6 Right reverse PWM duty cycle
TB2CCTL2 = OUTMOD_7; // CCR2 reset/set
TB2CCR2 = OFF; // P3.7 Left reverse PWM duty cycle
//------------------------------------------------------------------------------
}


void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = TIMERS_TRUE;
  if (five_msec_count < FIVE_SECS){ // FIVE_SECS = 1000
    five_msec_count++;
  }
//------------------------------------------------------------------------------

}
void five_msec_sleep(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = CLEAR_5MSEC;  //CLEAR_5MSEC=0
  while(fivemsec > (five_msec_count+TIME_INCREMENT)); // TIME_INCREMENT = 1
//------------------------------------------------------------------------------
}

void five_msec_delay(unsigned int delay){
  time_interval=CLEAR;
  while(delay > (time_interval+1));
}



