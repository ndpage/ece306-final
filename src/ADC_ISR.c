/*================================================================
    ADC_ISR.c - Interrupt Service Routine for the Analog to Digital Converter
  ECE 306 - Project 5
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
extern unsigned int channel;


//------------------------------------------------------------------------------
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
 switch(__even_in_range(ADC10IV,12)) {
 case 0: break; // No interrupt
 case 2: break; // conversion result overflow
 case 4: break; // conversion time overflow
 case 6: break; // ADC10HI
 case 8: break; // ADC10LO
 case 10: break; // ADC10IN
 case ADC_INPUTS:
    // Need this to change the ADC10INCH_x value.
      ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
        switch (channel){
          case LEFT_DETECT: //Left
          ADC10MCTL0 = ADC10INCH_1; // Next channel A1
          ADC_Left_Detector = ADC10MEM0; // Current Channel result for A0
          channel++;  
          break;
          case RIGHT_DETECT://Right
            ADC10MCTL0 = ADC10INCH_3; // Next channel A3
            ADC_Right_Detector = ADC10MEM0; // Current Channel result for A1
            channel++;
            break;
          case THUMB_WHEEL: //Thumb wheel
            ADC10MCTL0 = ADC10INCH_0; // Next channel A0
            ADC_Thumb = ADC10MEM0; // Current Channel result for A3
        
            channel=LEFT_DETECT;
            break;
            
          default:
            break;
  }
ADC10CTL0 |= ADC10ENC; // Turn on the ENC bit of the ADC10CTL0
ADC10CTL0 |= ADC10ENC + ADC10SC; // Start next sample.
break; 
default: break;
 }
}
//---------------------------------------------------
