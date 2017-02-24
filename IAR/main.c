#include "driverlib.h"
#include "mymsp430.h"
#include "textlcd.h"


/* Declaring Global Variable */

#define CS_PORT		GPIO_PORT_P2
#define CS_PIN		GPIO_PIN6

uint8_t adc_send_data[]={0x06,0x00,0x00};
uint8_t adc_receive_data[3],temp;
volatile uint16_t adc_value;
volatile float voltage=0;
TextLcd_4Bit_HandleTypeDef mylcd;
uint8_t lcd_buffer[16];



/* Declaring Interrupt Service Rountie */

#pragma vector=TIMER2_A1_VECTOR
__interrupt void TimerA2_ISR(void)
{
	Delay_Using_TimerA2_ISR();
}


void main( void )
{
	/* Stop watchdog timer */
	WDT_A_hold(WDT_A_BASE);

	/* Initialize clock Using DCO */
	Clk_Using_DCO_Init(16000,8000,SMCLK_CLOCK_DIVIDER_2);

	/* Initialize Delay Using Timer */
	Delay_Using_TimerA2_Init();

	/* Initialize Text LCD */
	textlcd_init(&mylcd,TextLcd_Dimension16xN,
				 GPIO_PORT_P2,GPIO_PIN0, //RS
				 GPIO_PORT_P2,GPIO_PIN2, //EN
				 GPIO_PORT_P3,GPIO_PIN4, //D4
				 GPIO_PORT_P3,GPIO_PIN5, //D5
				 GPIO_PORT_P3,GPIO_PIN6, //D6
				 GPIO_PORT_P3,GPIO_PIN7 //D7
				 );

	textlcd_puts(&mylcd,0,0,(uint8_t*)"ADC VALUE=",10);
	textlcd_puts(&mylcd,1,0,(uint8_t*)"VOLTAGE=",8);

	/* Initialize gpio for Led */
	GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN4);

	/* Initialize gpio for Chip select control */
	GPIO_setAsOutputPin(CS_PORT,CS_PIN);

	/* Disable chip slave */
	GPIO_setOutputLowOnPin(CS_PORT,CS_PIN);

	//Spi_Master_Init();
	Spi_Master_Init(USCI_A1_BASE,
			GPIO_PORT_P4,GPIO_PIN4, //MOSI
			GPIO_PORT_P4,GPIO_PIN5, //MISO
			GPIO_PORT_P4,GPIO_PIN0, //SCK
			1000000					//Frequency
			);


	while(1)
	{
		Spi_Master_Send_Receive_Data(USCI_A1_BASE,CS_PORT,CS_PIN,
				adc_send_data,adc_receive_data,3);

		adc_value=((adc_receive_data[1]&0x0f)<<8)|(adc_receive_data[2]);
		voltage=(adc_value/4095.0)*4.096;

		sprintf((char*)lcd_buffer,"%04d",adc_value);
		textlcd_puts(&mylcd,0,10,lcd_buffer,4);

		sprintf((char*)lcd_buffer,"%8.6f",voltage);
		textlcd_puts(&mylcd,1,8,lcd_buffer,8);

		GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN4);
		Delay_ms(500);
	}
}


