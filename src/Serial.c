/*================================================================
    Serial.c - Contains functions for transmitting
                 and receiving characters
  ECE 306 - Homework 8
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

extern volatile char USB_Char_Rx[LARGE_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx_A1[LARGE_RING_SIZE];
extern volatile char USB_Char_Tx_A1[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_wr_a1;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_rd_a1;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern unsigned int end_of_string;
extern volatile unsigned int SW1_pressed;
extern volatile unsigned int SW2_pressed;
char NCSU_str[10] = "NCSU  #1";
char Display[10];
extern unsigned int j;
extern unsigned int wait_time[SMALL_RING_SIZE];
extern char adc_char[5];
extern unsigned int time_interval;
unsigned int temp_rx;
extern volatile unsigned int char_received;
extern unsigned int command;
extern unsigned int send_response;
extern unsigned int password_set;
char im_here[8] = "Im here";
char Fast[22] = "A1 BAUD set to 115200";
char Slow[20] = "A1 BAUD set to 9600";
char set_IOT_115200[32] = "AT+S.SCFG=console1_speed,115200";
char set_IOT_9600[30] = "AT+S.SCFG=console1_speed,9600";
char k=0;
extern char array0[LARGE_RING_SIZE];
extern char array1[LARGE_RING_SIZE];
char port_fast[14] = "iot_port_fast";
extern char password[6];
char password_received[17] = "Password Correct";
extern char* ret_a0;
extern char* ret_a1;
unsigned int* beginning;
extern unsigned int receive_password;
extern unsigned int ip_set;
extern unsigned int speed;
extern unsigned int command_set;
extern unsigned int first_run;
extern volatile unsigned int string_count;
extern unsigned int rd_a1;
extern char command_array[20];
extern char* password_ptr;
extern volatile unsigned int string_received;
extern volatile unsigned int command_received;
extern volatile char *string;

//---------------------------------------------------
// Transmit string over A0
//----------------------------------------------------
void transmit_str_A0(char* str){
  int i=0;
  while(str[i]!='\0'){
   UCA0_transmit(str[i]);
   i++;
  }
}
//-----------------------------------------------------

//------------------------------------------------------
// Transmit string over A1
//-------------------------------------------------------
void transmit_str_A1(char* str){
  int i=0;
  while(str[i]!='\0'){
   UCA1_transmit(str[i]);
   i++;
  }
}
//-----------------------------------------------------------
//------------------------------------//
//Transmits a character over UCA0
//------------------------------------//
void UCA0_transmit(char Char){ // transmit to the computer
  if(char_received){
  while(UCA0STATW & UCBUSY);
    UCA0TXBUF=Char;
  } 
}

//------------------------------------//
//Transmits a character over UCA1
//------------------------------------//
void UCA1_transmit(char Char){ //transmit to the IOT module
    while(UCA1STATW & UCBUSY);
    UCA1TXBUF=Char;
}
//-------------------------------------------------------------------------
// receives characters on A0 -- From the PC
//------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
 unsigned int temp;
 switch(__even_in_range(UCA0IV,0x08)){
 case 0: // Vector 0 - no interrupt
 break;
 case 2: // Vector 2 - RXIFG
 char_received=1;
 temp = usb_rx_ring_wr;
 wait_time[temp]=time_interval;  //write time of receive to wait_time[]
 temp_rx=temp;
 USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
 //UCA0_transmit(USB_Char_Rx[temp]); // echo char typed back to the computer  
 //if(USB_Char_Rx[temp]!='\n'){
 UCA1_transmit(USB_Char_Rx[temp]);// transmit info from IOT module to PC
 //} 
// ret_a0 = strstr(array0,password);
 //array0[temp] = USB_Char_Rx[temp];
 
 if (++usb_rx_ring_wr >= (LARGE_RING_SIZE)){
 usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
 }
 break;
 
case 4: // Vector 4 – TXIFG
 break; 
 default: break;
 }

}
//-------------------------------------------------------------------------
// receives characters on A1 -- From IOT module
//------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
 unsigned int temp;
 switch(__even_in_range(UCA1IV,0x08)){
 case 0: // Vector 0 - no interrupt
 break;
 case 2: // Vector 2 - RXIFG
 temp = usb_rx_ring_wr_a1;
 wait_time[temp]=time_interval;  
 USB_Char_Rx_A1[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
 UCA0TXBUF=USB_Char_Rx_A1[temp];// transmit info from IOT modul
 
 if (++usb_rx_ring_wr_a1 >= (LARGE_RING_SIZE)){
 usb_rx_ring_wr_a1 = BEGINNING; // Circular buffer back to beginning
 }
 break;
 case 4: // Vector 4 – TXIFG
 break;
 default: break;
 }

 
}
//------------------------------------------------------------------
void Password(void){ 
  
  
   /*
   while((ret_a0+5) != &array0[usb_rx_ring_rd]){ //while the locations are not the same, make them the same
    usb_rx_ring_rd++;
  }
  */
}

void Command(void){
  int j=0;
  // If a command has been entered, determine command and speed
 while(command_array[j] != '\r'){ 
   command = command_array[j]; //set command
switch(command){
      // Movement commands                   
  case 'x': stop(); //call stop function
            display_4 = "Stop      ";
            posL4 = FIRST;
          //  lcd_out(display_4, LCD_HOME_L4, posL4);
            five_msec_delay(20);
            break;
  case 'f': //drive forward
            display_4 = "Forward  ";
            posL4 = FIRST;
           // lcd_out(display_4, LCD_HOME_L4, posL4);
            forward(); //call forward function
            five_msec_delay(50);
            stop();
            break;
  case 'b': //drive backwards
            display_4 = "Backwards ";
            posL4 = FIRST;
          //  lcd_out(display_4, LCD_HOME_L4, posL4);        
            reverse(); //call reverse function
            five_msec_delay(50);
            stop();
            break;
  case 'r': //turn right
            display_4 = "Right     ";
            posL4 = FIRST;
         //   lcd_out(display_4, LCD_HOME_L4, posL4);        
            right(); //call right function
            five_msec_delay(50);
            stop();
            break;
  case 'l': //turn Left
            display_4 = "Left      ";
            posL4 = FIRST;
          //  lcd_out(display_4, LCD_HOME_L4, posL4);        
            left(); // Call left function
            five_msec_delay(50);
            stop();
            break;
      }
 j++; 
 }
  
} 

void Clear_Command(void){
   //clear the command array
 j=0;
 while(command_array[j]!='\0'){
      command_array[j]='\0';
      j++;
  }
}


//---------------------------------------------------------------------------------------------------
//  Recieve function gets a char from A0 buffer, increments the value and transmit the value over A0
//------------------------------------------------------------------------------------------------
// Project 7 stuff 
void recieve_A0(void){  // recieve and transmit on A0
/*    
  if((usb_rx_ring_rd!=usb_rx_ring_wr) && (wait_time[usb_rx_ring_rd] < (time_interval-ONE_SEC)) ){
    HEXtoBCD(USB_Char_Rx[usb_rx_ring_rd]); //convert reieved character
    display_3 = adc_char; //send character to display
    UCA0_transmit((USB_Char_Rx[usb_rx_ring_rd]+BEGIN)); //usb_rx_ring_rd points to the value to read from buffer
    char_received=RESET; //reset character recieved flag
    
    if(++usb_rx_ring_rd>=SMALL_RING_SIZE){ //reset read index
      usb_rx_ring_rd=BEGINNING;
    }   
  
  }
*/  
 /* 
  if(end_of_string==ACTIVATED){ //if characters have been recieved 
    while(USB_Char_Rx[usb_rx_ring_rd] != '\0'){  //
        Display[j]=USB_Char_Rx[usb_rx_ring_rd];  //copy characters in buffer to Display[]
        j++;
        usb_rx_ring_rd++;
      }
       j=RESET; //reset 
    }
    display_4 = "          "; //clear the display  
    display_4 = Display; // display the recieved string on display line 4
    
    end_of_string=RESET; //reset    
    SW1_pressed=RESET;
*/ 
}
  
void transmit_A0(void){
/*
  if(SW1_pressed==ACTIVATED){
  while(NCSU_str[j] != '\0'){ //while there are letter in the string
      UCA0_transmit(NCSU_str[j]); //transmit "NCSU  #1" over UCA1
      j++;
    }
    UCA0_transmit(NCSU_str[j]); //transmit null character
    j=RESET; //reset 
  SW1_pressed = RESET; //reset
}*/
}
  

