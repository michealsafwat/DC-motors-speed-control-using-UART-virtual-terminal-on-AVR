

#include "MACROS_AND_UART.h" /* header file that includes function definitions and prototypes for using UART
							and also includes all the required macros*/
int main()
{
	/* the following three int variables hold the value of motors speeds ranging from 0 to 100 
	 taken from the user's keyboard through virtual terminal*/
	
	int SPEED_A;		// Speed of motor A		
	int SPEED_B;		// Speed of motor A	
	int SPEED_C;		// Speed of motor A	
	
	
	unsigned char* Received_Str;		// this pointer points to a char array that holds the string received through virtual terminal
	
	
/* the following three char arrays hold the speed portion of the string (data frame) received from virtual terminal in this format (000 , 001,...100)
  each array holds 3 char and the forth is the null (terminating char)*/

	char A[4];		// this array holds the speed of motor A 
	char B[4];		// this array holds the speed of motor C 
	char C[4];		// this array holds the speed of motor B
	
	
	/* to control the speed of the motors PWM is required so two 8 bit timers are used for that timer0 ,timer2.
		timer0 is used with motor A and motor B while timer2 is used with motor C.
		the following 3 8-bit registers are used to hold the speeds of each motor ranging from 0 to 255(highest value for highest speed )
		the registers are OC0A,OC0B and OC2A for motors A,B and C respectively*/
			
	DDRD=0x60;		/*initializing two pins of port D which are PD5,PD6 as output and they are OC0B,OC0A respectively 
	and these two pins generate the required PWM waveforms controlling the speed*/
	
	
	DDRB =0x08;		/* initializing PB3 as output which is OC2A that controls the speed of motor C*/
	
	
	
	
	while(1){
		
		
		USART_Init();						/* initializing UART peripheral defining its baud rate , parity mode ,stop bits , data bits 
												 and whether to use in asynchronous mode or not and enabling the receiver and transmitter*/
										 
		Received_Str=UART0_Rx_Str();		/* this variable holds the returned string from the function UART0_Rx_Str which is the data frame received by the UART */	
		
		
		/*this for loop is used to fill array A,B and C with the right portion of characters (motors speeds) from the received string from the virtual terminal*/
		for (int j=0;j<3;j++)
		{
			A[j]=Received_Str[j+1];		//puts characters from index 1 to 3 of the received string (motor A speed) in array A
			B[j]=Received_Str[j+5];		//puts characters from index 5 to 7 of the received string (motor B speed) in array B
			C[j]=Received_Str[j+9];		//puts characters from index 9 to 11 of the received string (motor C speed) in array C
			
		}
		
		SPEED_A = atoi(A);				// converts the speed of motor A from char array to integer 
		SPEED_B = atoi(B);				// converts the speed of motor B from char array to integer 
		SPEED_C = atoi(C);				// converts the speed of motor C from char array to integer 
		
		
		
		// the following is the setup of timer0 and timer2 to use PWM in order to control the speeds of the motors
		
		//settings for timer0
		TCCR0A|=(1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00);		/* select mode of operation to be Fast PWM 
																	and clear OC0A and OC0B on compare match, set OC0A and OC0B at BOTTOM, (non-inverting mode).*/	
		
		TCCR0B|=(1<<CS00)|(1<<CS02);								// select prescaler to be 1024
		
		//settings for timer2
		TCCR2A|=(1<<COM2A1)|(1<<WGM21)|(1<<WGM20);					 /* select mode of operation to be Fast PWM 
																		and clear OC2A  on compare match, set OC2A at BOTTOM, (non-inverting mode).*/	
		
		TCCR2B|=(1<<CS02)|(1<<CS22);								// select prescaler to be 1024
		
		
			
		if (Received_Str)					//if there is data received from the virtual terminal (keyboard) then use the data to control the motors speeds
		{
			OCR0A=Mapped_Speed_A;			//after mapping the value taken from the user put it in OCR0A register so supplies motor A with the required speed
			OCR0B=Mapped_Speed_B;			//after mapping the value taken from the user put it in OCR0B register so supplies motor B with the required speed
			OCR2A=Mapped_Speed_C;			//after mapping the value taken from the user put it in OCR2A register so supplies motor C with the required speed
		}
		
	}
	
	return 0;
}