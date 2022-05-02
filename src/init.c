/*================================================================
    Init.c - Initializes the LCD 
  ECE 306 - Homework 3
  Nathan Page 
    
  Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)  
==================================================================
*/

#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;

extern char display_line_1[LCD_SIZE]; //LCD string size = 11
extern char display_line_2[LCD_SIZE];
extern char display_line_3[LCD_SIZE];
extern char display_line_4[LCD_SIZE];
    
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern volatile char USB_Char_Rx[LARGE_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx_A1[LARGE_RING_SIZE];
extern volatile char USB_Char_Tx_A1[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr_a1;
extern volatile unsigned int usb_rx_ring_rd_a1;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr_a1;
extern volatile unsigned int usb_tx_ring_rd_a1;
extern volatile unsigned int char_received;
void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them.
  enable_interrupts();
  display_1 = &display_line_1[LCD_FIRST_POS]; 
  display_2 = &display_line_2[LCD_FIRST_POS];
  display_3 = &display_line_3[LCD_FIRST_POS];
  display_4 = &display_line_4[LCD_FIRST_POS];

//------------------------------------------------------------------------------
}
  void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}
void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ(USE_IOT_WAKEUP);
}

//------------------------------------------------------------------------------

void Init_Serial_UCA0(unsigned int rate, unsigned int frac_val){

 int i;
 for(i=0; i<SMALL_RING_SIZE; i++){
  USB_Char_Rx[i] = 0x00; // USB Rx Buffer
 }
 
 usb_rx_ring_wr = BEGINNING;
 usb_rx_ring_rd = BEGINNING;

 for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
  USB_Char_Tx[i] = 0x00; // USB Tx Buffer
 }
 usb_tx_ring_wr = BEGINNING;
 usb_tx_ring_rd = BEGINNING;
 // Configure UART 0
 UCA0CTLW0 = 0; // Use word register
 UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA0CTLW0 |= UCSWRST; // Set Software reset enable
 
// 9,600 Baud Rate
// 1. Calculate N = fBRCLK / Baudrate
// N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
// if N > 16 continue with step 3, otherwise with step 2
// 2. OS16 = 0, UCBRx = INT(N)
// continue with step 4
// 3. OS16 = 1,
// UCx = INT(N/16),
// = INT(N/16) = 833.333/16 => 52
// UCFx = INT([(N/16) – INT(N/16)] × 16)
//              = ([833.333/16-INT(833.333/16)]*16)
//              = (52.08333333-52)*16
//              = 0.083*16 = 1
// 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
// Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx  neg   pos  neg  pos
// 8000000 9600     1     52   1    0x49 -0.08 0.04 -0.10 0.14
  UCA0BRW = rate; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA0MCTLW = frac_val;
 UCA0CTL1 &= ~UCSWRST; // Release from reset
 UCA0IE |= UCRXIE; // Enable RX interrupt
}


void Init_Serial_UCA1(unsigned int rate, unsigned int frac_val){
 int i;
 for(i=0; i<SMALL_RING_SIZE; i++){
  USB_Char_Rx[i] = 0x00; // USB Rx Buffer
 }
 
 usb_rx_ring_wr_a1 = BEGINNING;
 usb_rx_ring_rd_a1 = BEGINNING;

 for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
  USB_Char_Tx[i] = 0x00; // USB Tx Buffer
 }
 usb_tx_ring_wr_a1 = BEGINNING;
 usb_tx_ring_rd_a1 = BEGINNING;
 // Configure UART 0
 UCA1CTLW0 = 0; // Use word register
 UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA1CTLW0 |= UCSWRST; // Set Software reset enable
 
// 9,600 Baud Rate
// 1. Calculate N = fBRCLK / Baudrate
// N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
// if N > 16 continue with step 3, otherwise with step 2
// 2. OS16 = 0, UCBRx = INT(N)
// continue with step 4
// 3. OS16 = 1,
// UCx = INT(N/16),
// = INT(N/16) = 833.333/16 => 52
// UCFx = INT([(N/16) – INT(N/16)] × 16)
//              = ([833.333/16-INT(833.333/16)]*16)
//              = (52.08333333-52)*16
//              = 0.083*16 = 1
// 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
// Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  UCA1BRW = rate; // 9,600 Baud
  
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA1MCTLW = frac_val;
 UCA1CTL1 &= ~UCSWRST; // Release from reset
 UCA1IE |= UCRXIE; // Enable RX interrupt
}
