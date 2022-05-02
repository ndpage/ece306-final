  //------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>
// Required defines
// In the event the universe no longer exists, this bit will reset

// Global Variables------------------------------------------------
      
    //Variables used for motor control
  char start_moving;
  char moving;
  

volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
volatile unsigned int SW1_pressed;
volatile unsigned int SW2_pressed;
volatile unsigned int SW1_debounce;
volatile unsigned int SW2_debounce;
volatile unsigned int SW1_count;
volatile unsigned int SW2_count;
// ADC variables
unsigned int ADC_Right_Detector;
unsigned int ADC_Left_Detector;
unsigned int ADC_Thumb;
unsigned int channel=0;
extern char adc_char[5];

char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
volatile unsigned int one_msec_count;
extern char display_line_1[LCD_SIZE];  //array size = 11
extern char display_line_2[LCD_SIZE];
extern char display_line_3[LCD_SIZE];
extern char display_line_4[LCD_SIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;

int shape = 0;
int count;
int count1;
int Stop;
unsigned int Go=0;

volatile unsigned int SW1_count;
volatile unsigned int SW2_count;

unsigned int display_flag_left;
unsigned int display_flag_right;
unsigned int display_flag_thumb;

unsigned int Right_White;
unsigned int Left_White;
unsigned int Right_Black;
unsigned int Left_Black;

unsigned int right_forward_rate;
unsigned int left_forward_rate;
unsigned int right_reverse_rate;
unsigned int left_reverse_rate;
unsigned int Direction;
unsigned int time_interval;

volatile char USB_Char_Rx[LARGE_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];
volatile char USB_Char_Rx_A1[LARGE_RING_SIZE];
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_wr_a1;
volatile unsigned int usb_rx_ring_rd; //<- A0
volatile unsigned int usb_rx_ring_rd_a1; //<- A1
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_wr_a1;
volatile unsigned int usb_tx_ring_rd;
volatile unsigned int usb_tx_ring_rd_a1;



extern unsigned int temp;
unsigned int j;
unsigned int end_of_string;
unsigned int wait_time[16];
volatile unsigned int char_received=0;
volatile unsigned int drive_time;

unsigned int thumb;
unsigned int command;
unsigned int send_response=0;
unsigned int receive_password;
unsigned int password_set;
unsigned int ip_set;
char* ret_a0;
char* ret_a1;
unsigned int a0_string_received=0;
unsigned int a1_string_received=0;
unsigned int speed;
unsigned int command_set;
unsigned int first_run=1;
char array0[LARGE_RING_SIZE];
char array1[LARGE_RING_SIZE];
char* ip_address=0;
char display1[10];
char display2[3];
volatile unsigned int string_count;
unsigned int i;
unsigned int j;
unsigned int rd_a0;
unsigned int rd_a1;
char command_array[20];
char* password_ptr;
unsigned int ip_found=1;
volatile unsigned int string_received;
volatile unsigned int command_received;
unsigned int set_ipaddr;
volatile char *string;
unsigned int index;
unsigned int put_in_buf;
char Command_Buf[50];
unsigned int ip_address_found;
unsigned int move_command_found;
unsigned int current_command;
unsigned int now=0;
unsigned int reset;
void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
 Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System
  Init_Conditions();

  Time_Sequence = TIME_RESET;                //
  Init_Timers();                            // Initialize Timers
  //five_msec_sleep(QTR_SEC);               // 250 msec delay for the clock to settl
  Init_LCD();                 // Initialize LCD
  Init_ADC();
  
  Init_Serial_UCA0(BAUD_9600,BAUD_9600_MCTLW);
  Init_Serial_UCA1(BAUD_9600,BAUD_9600_MCTLW);
  /*
  display_1 = "Left ";
  posL2 = FIRST;
  display_2 = "Right ";
  posL2 = FIRST;
 */
 // display_3 = "Thumb ";
 // posL3 = FIRST;
 // display_1 = "Baud Rate";
  Display_Process();
  ADC_Process();
 
  
  five_msec_delay(100);
  PJOUT |= IOT_RESET;
  P3OUT &= ~IR_LED;
  P1OUT &= ~LCD_BACKLITE; // LCD_BACKLITE Port Pin set high
  ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
  //------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------ 
// MAC Address -> 00:80:E1:B4:32:8E
// Get IP address -> AT+S.STS=ip_ipaddr  
 //five_msec_delay(10);
 // transmit_str_A1("AT+S.STS=ip_ipaddr\r");
j=RESET;
 
 
 while(ALWAYS) { // Can the Operating system run    
   //update appropriate parts of the display at an appropriate interval
    //update_display();
  //  main_menu();
//  if(display_flag_left>2000){
//      PJOUT &= ~IOT_RESET;
//      five_msec_delay(10);
//      PJOUT |= IOT_RESET;  
//   }
   
   if(rd_a1 != usb_rx_ring_wr_a1){ //if a character has been sent
      switch(USB_Char_Rx_A1[rd_a1]){
          case'L': put_in_buf=1;
                   index=0;
                   Command_Buf[index] = USB_Char_Rx_A1[rd_a1];
                   index++;
                   break;
          
          case'q': put_in_buf=1;
                   index=0;
                   Command_Buf[index] = USB_Char_Rx_A1[rd_a1];
                   index++;
                   break;
          case'+': 
          case'#':
		   put_in_buf=1;
                   index=0;
                   Command_Buf[index] = USB_Char_Rx_A1[rd_a1];
                   index++;
                   break;
		
          default: 
		if(put_in_buf){
			Command_Buf[index]=USB_Char_Rx_A1[rd_a1];
                        index++;
                        if(index>49){
                          index=49;
                        }
                        if(Command_Buf[0]=='L'){
                          if(Command_Buf[1]=='F'){
                               if(Command_Buf[2]=='1'){
                                  now=1;
                               }
                               else if(Command_Buf[2]=='0'){
                                  stop();
                                  TB1CCR1=6000;
                                  TB1CCR2=6500;
                                  five_msec_delay(200);
                                  stop();
                               }
                            }
                        }
                        
                       if(Command_Buf[0]=='q'){
                         if(Command_Buf[1]=='1'){
                           if(Command_Buf[2]=='2'){
                             if(Command_Buf[3]=='3'){
                               if(index>=6){  
                                current_command=4;
                                while(Command_Buf[current_command]!='\0'){  
                                 switch(Command_Buf[current_command]){
                                   case'f':stop();
                                           TB1CCR1=6000;
                                           TB1CCR2=6500;
                                           break;
                                           
                                   case'b':stop();
                                           TB2CCR1=6500;
                                           TB2CCR2=6000;
                                           break;
                                           
                                   case'r':stop();
                                           TB1CCR2=4000;
                                           TB2CCR1=4000;
                                           break;
                                           
                                   case'l':stop();
                                           TB1CCR1=4000;
                                           TB2CCR2=4000;
                                           break;       
                                           
                                   case'x':stop();
                                           break;
                                           
                                   case'1': 
                                            five_msec_delay(50);
                                            stop();
                                            break;
                                   case'2': 
                                            five_msec_delay(100);
                                            stop();
                                            break;
                                   case'3':
                                            five_msec_delay(250);
                                            stop();
                                           break;
                                   case'4':
                                            five_msec_delay(350);
                                            stop();
                                           break;      
                                   case'5':
                                           five_msec_delay(500);
                                            stop();
                                           break;
                                  }//end of Switch
                                 current_command++; 
                                 }// while 
                                  for(i=0;i<50;i++){
                                    Command_Buf[i]='\0';
                                  }
                               }
                               }             
                              }  
                            }
                          }
                        
                        else if(index>=7){
				if(Command_Buf[0]=='+'){
					if(Command_Buf[6]=='2'){
                                              if(Command_Buf[7]=='1'){
                                                  display_1 = "Scanning";
                                                  posL1=FIRST;
                                                  lcd_out(display_1, LCD_HOME_L1, posL1);
                                                }
                                              else if((Command_Buf[7]=='4')&&(index>28)){
                                                
                                                  display_ip_addr();
                                                  
                                                
                                                display_1 = "Connected ";
                                                display_2=display1;
                                                display_3=display2;
                                                display_4 = "          ";
                                                update_display();
                                                 for(i=0;i<50;i++){
                                                    Command_Buf[i]='\0';
                                                  }
                                             }           
                                    }
                                }
                          }        
               }
          break;
      
    }//end of switch
      if(++rd_a1 >= (LARGE_RING_SIZE)){
          rd_a1 = BEGINNING; // Circular buffer back to beginning
         }    
   }// end of if(rd!=wr)	
 
 //Call functions to perform line following  
    if(now==BEGIN){ //if SW1 is pressed, look for black line
      P3OUT |= IR_LED;
      ADC_Process();
      Detect();
    }
   else if(now==DETECT){ // if line is found, start line follow 
      Start();
    }
   else if(now==FOLLOW){ //Maintain line following 
      Follow();
    } 
    
    
  
  //  Copy string from buffer to array1
   // look for commands in array1 using string functions
  /*
  if((strstr(array0,"+WIND:21"))!='\0'){ //+WIND:21 = Wifi scanning
         ClrDisplay();
        display_1 = "Scanning";
        //update_display();
      }
  if((strstr(array0,"+WIND:24")) != '\0'){ //if ip address found
      ip_address = strstr(array0,"+WIND:24");
      while(ip_address!=&array0[rd_a0]){
        if(++rd_a0 >= (LARGE_RING_SIZE)){
            rd_a0 = BEGINNING; // Circular buffer back to beginning
          }
      }
      display_ip_addr();
    }
// Look for command 
  if((strstr(array0,"q11"))!= '\0'){   
     password_ptr = strstr(array0,"q11"); //look for password
     get_command();
     Command();
     Clear_Command();
  }

*/   
/*
 if(Go){
  PJOUT&=~IOT_RESET;
  five_msec_delay(10);
  PJOUT|=IOT_RESET;
  Go=0;
 }
 */
  } // end of While(ALWAYS)

} //end of Main


















