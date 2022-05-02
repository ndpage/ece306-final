/*================================================================
  String Process- con
  ECE 306 - Project 9
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/

#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern char* ip_address;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern char command_array[20];
extern char* password_ptr;
extern unsigned int rd_a0;
extern char array0[LARGE_RING_SIZE];
extern char Command_Buf[50];
extern char display1[10];
extern char display2[3];
extern unsigned int index;
//-------------------------------------------------------------------------
// Display the IP address
//----------------------------------------------------------------------
void display_ip_addr(void){

  int j;
  int i; //set index to first char in IP address
       j=17;
        for(i=0;i<10;i++){
          display1[i]=Command_Buf[j];
          j++;
         }
       for(i=0;i<2;i++){
          display2[i]=Command_Buf[j];
          j++;
        }
}
//----------------------------------------------------------------------
// Get the command if password has been set
//----------------------------------------------------------------------
void get_command(void){
  int i=0;
       display_1 = "Pass Set";
       while(password_ptr != &array0[rd_a0]){
         if(++rd_a0 >= (LARGE_RING_SIZE)){
                rd_a0 = BEGINNING; // Circular buffer back to beginning
             }
       }
       while(array0[rd_a0]!='\r'){ //copy commands into command array
           command_array[i]=array0[rd_a0];
           if(++rd_a0 >= (LARGE_RING_SIZE)){
               rd_a0 = BEGINNING; // Circular buffer back to beginning
            } 
           i++;
         }
         command_array[i]='\r';
         i=RESET; 
          
 //password_ptr+=3;        
//     
//         i=0; //start at the command 
//         while(*(password_ptr+i)!='\r'){ //copy commands into command array
//           command_array[i]=*(password_ptr+i);
//            i++;
//         }
//         command_array[i]='\r';
//         i=RESET;   
}