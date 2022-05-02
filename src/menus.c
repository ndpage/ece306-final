/*================================================================
   menus.c  - Contains code to select items from a menu
              by using the thumb wheel to chose the item,
              and SW1 to select the item. SW2 acts as a "back" button. 
                 
  ECE 306 - Homework 9
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/
#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern unsigned int ADC_Right_Detector;
extern unsigned int ADC_Left_Detector;
extern unsigned int ADC_Thumb;
extern unsigned int display_flag_left;
extern unsigned int display_flag_right;
extern unsigned int display_flag_thumb;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern unsigned int thumb;
extern volatile unsigned int SW1_pressed;
extern volatile unsigned int SW2_pressed;

void main_menu(void){
  thumb = (ADC_Thumb>>2);  //bitshift ADC_Thumb 1 => 6 bits to work with, each menu is 25 dec values wide
  
  if((thumb>=1)&&(thumb<25)){  // 1-25 = 9600 BAUD     ADC_Thumb
      display_2 = "9600      ";
      update_display();
      if(SW2_pressed){
         Init_Serial_UCA0(BAUD_9600,BAUD_9600_MCTLW);
         Init_Serial_UCA1(BAUD_9600,BAUD_9600_MCTLW);
      }
}
  else if((thumb>=25)&&(thumb<75)){ // 25-50 = 115200 BAUD
      display_2 = "115200   ";
      update_display();
      if(SW2_pressed){
         Init_Serial_UCA0(BAUD_115200,BAUD_115200_MCTLW);
         Init_Serial_UCA1(BAUD_115200,BAUD_115200_MCTLW);
      }
  }
  else if((thumb>=75)&&(thumb<125)){ //50-75 
      display_2 = "->Test    ";  
      update_display();
     }       

  else if((thumb>=125)&&(thumb<150)){ //50-75 
      display_2 = "////////////";  
      update_display();
    } 
 
}
//-----------------------------------------------------------------

void resistor_codes(void){

}



