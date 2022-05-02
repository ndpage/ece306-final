/*=============================================================
    functions.h
  ECE 306 - Homework 3
  Nathan Page
  - List of macros for all functions in the program  
 Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)   
================================================================
*/
extern unsigned int Right_White;
extern unsigned int Left_White;
extern unsigned int Right_Black;
extern unsigned int Left_Black;
//======= Main ==========
#define FIVE_SEC (10000*five_msec_count)
#define ONE_AND_QTR_SEC 250
#define ONE_SEC 200
#define THREE_QTR_SEC 150 
#define HALF_SEC 100
#define QTR_SEC 50
#define COUNT_RESET 0
#define BIG_RESET 0
#define BIG_SET 1
#define SPACES4 4
#define SPACES3 3
#define SPACES2 2
#define SPACES1 1
#define SIZE_COMPARE 5
  //MOTOR CONTROL
#define ENABLE 1
#define DISABLE 0
// Project 7
#define INIT 1



//======= Timers ========
#define TIMERS_TRUE 1
#define TIME_RESET 0
#define CLEAR_5MSEC 0
#define FIVE_SECS 1000
#define TIME_INCREMENT 1
#define TA0CCR0_INTERVAL 2500 //2500 interveral -> 5 msec (.005 sec) based upon Timer A0 configuration
#define COUNT_CLEAR 0
#define OFF 0
#define WHEEL_PERIOD 10000
#define DUTY_20 2000
#define DUTY_30 3000
#define DUTY_40 4000
#define DUTY_50 5000
#define DUTY_60 6000
#define DUTY_70 7000


#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States

#define CNTL_STATE_INDEX        (3)
// LCD
#define LCD_HOME_L1	        0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0
#define LCD_SIZE  11
#define LCD_FIRST_POS 0

// ======== PORTS ========
#define CLEAR 0x00
// Configure Port 1 -------------------------------------------------------------
#define V_DETECT_R (0x01) // Voltage from Right Detector
#define V_DETECT_L (0x02) // Voltage from Right Detector
#define LCD_BACKLITE (0x04) // Control Signal for LCD_BACKLITE
#define V_THUMB (0x08) // Voltage from Thumb Wheel
#define SPI_CS_LCD (0x10) // LCD Chip Select
#define RESET_LCD (0x20) // LCD Reset 
#define SIMO_B (0x40) // SPI mode - slave in/master out of USCI_B0
#define SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0
//------------------------------------------------------------------------------

// Configure Port 2 -------------------------------------------------------------
#define USB_TXD (0x01) // TRANSMITS USB DATA OUT
#define USB_RXD (0x02) // RECEIVES USB DATA IN
#define SPI_SCK (0x04) // CLOCK DATA
#define UNKNOWN1 (0x08) // UNKNOWN1
#define UNKNOWN2 (0x10) // UNKNOWN2
#define CPU_TXD (0x20) //  TRANSMITS CPU DATA
#define CPU_RXD (0x40) // RECEIVES CPU DATA 
#define UNKNOWN3 (0x80) // UNKNOWN 3
//------------------------------------------------------------------------------

// Configure Port 3 -------------------------------------------------------------
#define X1 (0x01) // 
#define Y1 (0x02) // 
#define Z1 (0x04) // 
#define IR_LED (0x08) // 
#define R_FORWARD (0x10) // Output for right motor -> forward
#define L_FORWARD (0x20) // Output for left motor -> forward 
#define R_REVERSE (0x40) // Output for right motor -> Reverse
#define L_REVERSE (0x80) // Output for left motor -> Reverse
//------------------------------------------------------------------------------

// Configure Port 4 ------------------------------------------------------------
#define SW1 (0x01) // Switch 1
#define SW2 (0x02) // Switch 2

//------------------------------------------------------------------------------

// Configure Port J---------------------------------------------------
#define IOT_WAKEUP (0x01) //set wake up
#define IOT_FACTORY (0x02) //
#define IOT_STA_MINIAP (0x04) //
#define IOT_RESET (0x08) //
//-------------------------------------------------------------------

//MACROS FROM CLOCKS==========================================================
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK             (0x01) // Any incorrect password locks registers

// Port J Pins
#define USE_IOT_WAKEUP  (0x00)
#define USE_SMCLK       (0x01)
#define XINR           (0x10) // XINR
#define XOUTR          (0x20) // XOUTR
#define CLEAR_REGISTER (0x0000)

// MOTOR CONTROL==============================================================
#define CIRCLE 1
#define FIG_8 2
#define TRIANGLE 3
#define CIRCLE_DELAY 20
#define LEFT_CIRCLE_DELAY 10
#define RIGHT_CIRCLE_DELAY 10
#define ONE_CIRCLE_TIMESEQ 5 
#define TWO_CIRCLES 520
#define CIRCLE_COUNT1 20
#define ONE_CIRCLE 20
    // circle()
#define CIRCLE_ON_DELAY 8
#define CIRCLE_OFF_DELAY 20
    //left_circle()
#define LEFT_CIR_ON 395
#define LEFT_CIR_ON_DELAY 5
#define LEFT_CIR_OFF_DELAY 20
     // right_circle()
#define RT_CIR_ON 390
#define RT_CIR_ON_DELAY 5
#define RT_CIR_OFF_DELAY 20
     // figure8()
#define FIG8_FORWARD_DELAY 5
     // triangle()
#define TRI_ON_DELAY 60
#define TRI_OFF_DELAY_1 80
#define TRI_OFF_DELAY_2 82
#define TRI_OFF_DELAY_3 84


// SWITCH======================================================================
#define NUM_OF_SHAPES 3
#define BUTTON_PRESS 15
#define SHAPE ((shape)-1)
#define FUNCTION_DELAY 15

// interrupt_ports =============================================================
#define ACTIVATED 1
#define TA0_REG_INTERVAL 15000
#define TA0CCR1_INTERVAL 15000
#define TA0CCR2_INTERVAL 20000
#define INTERRUPT 0
#define SWITCH_1 2
#define SWITCH_2 4
#define OVERFLOW 14
#define RESET 0

// interrupt_timers =============================================================
#define TIMER_INTERUPTS_10 10
// ADC_ISR ======================================================================
#define RESET_STATE 0

#define RIGHT_WHITE ((Right_White+50))
#define LEFT_WHITE ((Left_White+50))
#define RIGHT_BLACK ((Right_Black-100))
#define LEFT_BLACK ((Left_Black-100))
#define WHITE (((Right_White+Left_White)>>1))
#define BLACK (((Right_Black+Left_Black)>>1))

#define THRESHOLD 100
#define SPACE_6 6

// ADC_ISR 
#define ADC_INPUTS 12
#define LEFT_DETECT 0x00
#define RIGHT_DETECT 0x01
#define THUMB_WHEEL 0x02
#define REFRESH 50
#define THUMB_REFRESH ((REFRESH-10))
#define CAL_WHITE 100
#define FIRST 0
// Line follow==================================================================
#define BEGIN 1 
#define DETECT 2
#define FOLLOW 3
#define UNO_SECOND 100
#define THREE_TENTHS_SECOND 30
#define FIVE_TENTHS_SECOND 50
#define SIX_TENTHS_SECOND 60
#define SEVEN_TENTHS_SECOND 70
#define FORWARD (((ADC_Right_Detector + ADC_Left_Detector) > BLACK) )
#define RIGHT ( ((ADC_Right_Detector-ADC_Left_Detector) > WHITE) )
#define LEFT ( ((ADC_Right_Detector-ADC_Left_Detector) < WHITE) )
#define THIRD_QUAD 400

// Serial Communication=========================================================
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (64)
#define BAUD_9600 52
#define BAUD_115200 4
#define BAUD_9600_MCTLW 0x4911
#define BAUD_115200_MCTLW 0x5551
#define FIRST_ITEM 100
#define SECOND_ITEM 200
//=====================================================================
#define PASSWORD_SIZE 5
#define IP_ADDRESS 17

