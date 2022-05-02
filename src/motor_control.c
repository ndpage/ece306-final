/*==============================================================
   Motor Control - Contains ports declerations for I/O  
  ECE 306 - Homework 3
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/
#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern char start_moving;
extern char moving;
extern volatile unsigned int Time_Sequence;
extern int count1;
extern int count2;
extern unsigned int speed;
//-----------------------------------------------------------
void right(void){
  stop();
  speed='1';
  switch(speed){  
    case '1': TB2CCR1 = 3000; //  turn right fast
              TB1CCR2 = 3000;
              break;
    case '2': TB2CCR1 = 6000; //turn right medium
              TB1CCR2 = 6000;
              break;
    case '3': TB2CCR1 = 9000; //turn right slow
              TB1CCR2 = 9000;
              break;
   
 //   five_msec_delay(5);         
  }   
}
//-----------------------------------------------------------
void left(void){
  stop();
  speed='1';
  switch(speed){
    case '1': TB1CCR1 = 3000; //turn left fast
              TB2CCR2 = 3000;
              break;
    case '2': TB1CCR1 = 6000;//turn left medium
              TB2CCR2 = 6000;
              break;
    case '3': TB1CCR1 = 9000; //turn left slow
              TB2CCR2 = 9000;
              break;
   
   //five_msec_delay(5);        
  } 
}
//--------------------------------------------------------------
//Sets both motors to reverse------------------------------------
void reverse(void){
  stop();
  speed='1';
 switch(speed){
  case '1':TB2CCR1 = 3000;
           TB2CCR2 = 3000;
           break;
 case '2': TB2CCR1 = 6000;
           TB2CCR2 = 6000;
           break;
 case '3': TB2CCR1 = 9000;
           TB2CCR2 = 9000;
           break;
 
 // five_msec_delay(5);         
  } 
}
//--------------------------------------------------------------------
//Sets both motors to forward-------------------------------------
void forward(void){
 stop();
 speed='2';
 switch(speed){
  case '1':TB1CCR1 = 3000;
           TB1CCR2 = 3500;
           break;
 case '2': TB1CCR1 = 6000;
           TB1CCR2 = 6500;
           break;
 case '3': TB1CCR1 = 9000;
           TB1CCR2 = 9500; 
           break;
// five_msec_delay(5);          
 }
 
}//--------------------------------------------------------------------
// Stops all movement-------------------------------------------
void stop(void){
  
  TB1CCR1 = OFF;  //forward stop
  TB1CCR2 = OFF;
  
  TB2CCR1 = OFF; //reverse stop
  TB2CCR2 = OFF;
}//--------------------------------------------------------------------

// Circle produces code to complete 1 circle------------------------
void circle(void){
  count1=CLEAR;
  Time_Sequence=CLEAR;
  
  while(Time_Sequence<TWO_CIRCLES){ 
  P3OUT |= R_FORWARD;
   P3OUT |= L_FORWARD;
   five_msec_sleep(CIRCLE_ON_DELAY);
   P3OUT &= ~L_FORWARD;
   five_msec_sleep(CIRCLE_OFF_DELAY);
  Time_Sequence++;
   }
    
   stop();
}//--------------------------------------------------------------------



// Produces code to complete 1 left circle------------------------
void left_circle(void){
 Time_Sequence=CLEAR;
  
  while(Time_Sequence<LEFT_CIR_ON){ 
  P3OUT |= R_FORWARD;
   P3OUT |= L_FORWARD;
   five_msec_sleep(LEFT_CIR_ON_DELAY);
   P3OUT &= ~L_FORWARD;
   five_msec_sleep(LEFT_CIR_OFF_DELAY);
  Time_Sequence++;
   }
    
   stop();
}//--------------------------------------------------------------------

// Produces code to complete 1 right circle------------------------
void right_circle(void){
 
  Time_Sequence=CLEAR;
  
  while(Time_Sequence<RT_CIR_ON){ 
  P3OUT |= R_FORWARD;
   P3OUT |= L_FORWARD;
   five_msec_sleep(RT_CIR_ON_DELAY);
   P3OUT &= ~R_FORWARD;
   five_msec_sleep(RT_CIR_OFF_DELAY);
  Time_Sequence++;
   }
    
   stop();

}//--------------------------------------------------------------------

// Produces code to complete 1 figure 8-------------------------------
void figure8(void){
  left_circle();
  P3OUT |= R_FORWARD;
  P3OUT |= L_FORWARD;
  five_msec_sleep(FIG8_FORWARD_DELAY);
  right_circle();
  P3OUT |= R_FORWARD;
  P3OUT |= L_FORWARD;
  five_msec_sleep(FIG8_FORWARD_DELAY);
   stop();
}//--------------------------------------------------------------------


// Produces code to complete 1 triangle--------------------------------
void triangle(void){
  
    P3OUT |= R_FORWARD;
    P3OUT |= L_FORWARD;
   five_msec_sleep(TRI_ON_DELAY);
   P3OUT &= ~L_FORWARD;
   five_msec_sleep(TRI_OFF_DELAY_1);
   
     P3OUT |= R_FORWARD;
    P3OUT |= L_FORWARD;
   five_msec_sleep(TRI_ON_DELAY);
   P3OUT &= ~L_FORWARD;
   five_msec_sleep(TRI_OFF_DELAY_2);
   
     P3OUT |= R_FORWARD;
    P3OUT |= L_FORWARD;
   five_msec_sleep(TRI_ON_DELAY);
   P3OUT &= ~L_FORWARD;
   five_msec_sleep(TRI_OFF_DELAY_3);

   stop();
}//--------------------------------------------------------------------










