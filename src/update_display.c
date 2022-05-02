// update display
/*================================================================
   update_display.c  updates the display on a periodic basis
                      run from interrupt_timers
  ECE 306 - Homework 6
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
extern char adc_char[5];
extern unsigned int Go;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern char Display[10];
extern unsigned int time_interval;

void update_display(void){
  
if(display_flag_thumb>=150){
    posL1 = FIRST;
    posL2 = FIRST;
    posL3 = FIRST;
    posL4 = FIRST;
    lcd_out(display_1, LCD_HOME_L1, posL1);
    lcd_out(display_2, LCD_HOME_L2, posL2);
    lcd_out(display_3, LCD_HOME_L3, posL3);
    lcd_out(display_4, LCD_HOME_L4, posL4);
display_flag_thumb=RESET;
}
 /*
 HEXtoBCD(ADC_Left_Detector); //Convert left detector value using HEXtoBCD function
    display_1 = adc_char;
    posL1 = SPACE_6;
    if(display_flag_left==REFRESH){ //refresh the display
      lcd_out(display_1, LCD_HOME_L1, posL1); //refresh line 1 of the LCD
      display_flag_left=CLEAR;
    }
    HEXtoBCD(ADC_Right_Detector); //Convert right detector value using HEXtoBCD function
    display_2 = adc_char;
    posL2 = SPACE_6;
    if(display_flag_right==REFRESH){ //refresh the display
      lcd_out(display_2, LCD_HOME_L2, posL2); //refresh line 2 of the LCD
      display_flag_right=CLEAR;
    }
*/
   // HEXtoBCD(ADC_Thumb); //Convert thumb wheel value using HEXtoBCD function
   // display_3 = adc_char;
   // posL3 = SPACE_6;
   // if(display_flag_thumb==REFRESH){ //refresh the display
     // lcd_out(display_3, LCD_HOME_L3, posL3); //refresh line 3 of the LCD 
    //  display_flag_thumb=CLEAR;
    //}
 

}