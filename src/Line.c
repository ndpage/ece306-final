/*============================
    Line.c - Contains void Detect(void), void Start(void), and void Follow(void)
              which allows the car to follow a black line
  ECE 306 - Project 6
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==============================
*/

#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern unsigned int ADC_Right_Detector;
extern unsigned int ADC_Left_Detector;
extern unsigned int ADC_Thumb;
extern unsigned int Left_White;
extern unsigned int Right_White;
extern unsigned int Left_Black;
extern unsigned int Right_Black;
extern unsigned int right_forward_rate;
extern unsigned int left_forward_rate;
extern unsigned int right_reverse_rate;
extern unsigned int left_reverse_rate;

extern unsigned int time_interval;
extern unsigned int Go;
extern unsigned int Direction;
extern char *display_4;
extern char posL4;

//-----------------------------------------------------------------
// The Detect function drives forward
//  until the black line is detected by both detectors
//-------------------------------------------------------------------
void Detect(void){
  stop();  
  //go forward
  TB1CCR1=5000; //right forward
  TB1CCR2=5500;  //left forward
  five_msec_delay(600);
  
  if((ADC_Right_Detector>200)||(ADC_Left_Detector>200)){
    stop();
  }
  
  Go++; // Start Follow function  
}//-------------------------------------------------------------------


//--------------------------------------------------------------------
// The Start function initializes the motion of the car
//     once the line has been detected
//-----------------------------------------------------------------
void Start(void){ 
  stop();
  display_4 = "Waiting  "; // 
 // lcd_out(display_4, LCD_HOME_L4, posL4); 
  five_msec_delay(UNO_SECOND); //wait for 1 second
  // back up a little
    TB2CCR1=DUTY_30;
    TB2CCR2=DUTY_30;
    five_msec_delay(THREE_TENTHS_SECOND);
      stop();
  //rotate CCW 
   
//   TB1CCR1=DUTY_40;               //right forward
//   TB2CCR2=DUTY_40;               //left reverse
//   five_msec_delay(FIVE_TENTHS_SECOND);
//   stop();
   //Start going forward
   TB1CCR1=DUTY_30;
   TB1CCR2=DUTY_30;
   five_msec_delay(THREE_TENTHS_SECOND);
  stop();
   // lcd_out(display_4, LCD_HOME_L4, posL4); 
   Go++; //increment Go to next stage
}//---------------------------------------------------------------------

//------------------------------------------------------------------
 //  void Follow(void);

// The Follow function constantly monitors both detectors
//  and takes appropriate action if the car drives off the black line
//----------------------------------------------------------------------
void Follow(void){
     display_4="Follow   ";
     //lcd_out(display_4, LCD_HOME_L4, posL4); 
      //if both detectors are on black, go forward
     if((ADC_Right_Detector + ADC_Left_Detector) > BLACK){       // (ADC_Right_Detector + ADC_Left_Detector) > BLACK 
        stop();
       TB1CCR1=DUTY_40; //go forward
       TB1CCR2=DUTY_40;
        }
     //if right detector is on black and  left detector is on white, turn right
     if((ADC_Right_Detector-ADC_Left_Detector) > WHITE){        //(ADC_Right_Detector-ADC_Left_Detector) > WHITE
       stop();
      // turn right
       TB1CCR2=DUTY_60;
       TB2CCR1=DUTY_20;
     }
     // if right detector is on white and left is on black, turn left
     if((ADC_Right_Detector - ADC_Left_Detector) < WHITE){      //(ADC_Right_Detector-ADC_Left_Detector) < WHITE
       stop();
       // turn left
       TB1CCR1 = DUTY_60;
       TB2CCR2 = DUTY_20; 
     }
} 
//------------------------------------------------------------------------------







      