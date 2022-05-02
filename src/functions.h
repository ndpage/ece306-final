/*==================================================================
    functions.h
  ECE 306 - Homework 3
  Nathan Page
  -Function prototypes for all functions in the program 
 Built with IAR Embedded Workbench Version: 7.4.2.4369 (6.50.1)   
=====================================================================
*/
// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
//void Init_LEDs(void);
void Display_Process(void);
void five_msec_sleep(unsigned int fivemsec);
void Timer_code(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
__interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(int);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void grab_a_character(void);
int wait_for_character(void);
void menu(void);
void update_display(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
// Motor control
void forward(void);
void stop(void);
void reverse(void);
void right(void);
void left(void);
void circle(void);
void left_circle(void);
void right_circle(void);
void figure8(void);
void triangle(void);
// Custom Timer
void five_msec_delay(unsigned int delay);
// ADC Process
void ADC_Process(void);
void Init_ADC(void);
void HEXtoBCD(int hex_value);

//Line follow
void Detect(void);
void Follow(void);
void Find(void);
void Start(void);
void DetectAndFollow(void);
// Menu
void main_menu(void);
// Serial Communications
void Init_Serial_UCA0(unsigned int rate, unsigned int frac_val);
void Init_Serial_UCA1(unsigned int rate, unsigned int frac_val);
void UCA0_transmit(char Char);
void UCA1_transmit(char Char);
void transmit_str_A0(char* str);
void transmit_str_A1(char* str);
void transmit_recieve_str(void);
void transmit_A0(void);
void recieve_A0(void);
void Command(void);
void Password(void);
void Clear_Command(void);

// String Process
void display_ip_addr(void);
void get_command(void);

