#include <libopencm3/lm4f/systemcontrol.h>
#include <libopencm3/lm4f/rcc.h>
#include <libopencm3/lm4f/gpio.h>
#include <libopencm3/lm4f/uart.h>
#include <libopencm3/lm4f/timer.h>

void my_putchar(unsigned char ch)
{
	uart_send_blocking(UART0, ch);
}

void my_puts(char *buf)
{
	int i=0; // nbre de caractère initialisé à 0
	char tmp=0; // caractere actuels
	do
	{
		tmp=buf[i];
		i++;
		my_putchar(tmp);
	}
	while(tmp !='\0'); // on boucle tant qu'on n'est pas arrivé à l'\0
}

void delay(unsigned int delay)
{
	volatile unsigned int i;
	for(i=0;i<delay;i++)
		__asm__("nop");
}


void init_gpio(void)
{
	gpio_enable_ahb_aperture();
	periph_clock_enable(RCC_GPIOF);
	gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
	gpio_set_output_config(GPIOF, GPIO_OTYPE_PP, GPIO_DRIVE_2MA, GPIO2);
}

void clock_setup(void)
{
//	rcc_sysclk_config(OSCSRC_MOSC, XTAL_16M, 5) ; // PLL_DIV_80MHZ); // from GPIO
}


void led_set(int msk)
{
	gpio_set(GPIOF, GPIO2);
}

void led_clr(int msk)
{
	gpio_clear(GPIOF, GPIO2);
}

void usart_setup(void)
{
	periph_clock_enable(RCC_GPIOA);       // Enable GPIOA in run mode. 
	gpio_set_af(GPIOA, 1, GPIO0 | GPIO1); // Mux PA0 and PA1 to UART0 (alternate function 1) 
	periph_clock_enable(RCC_UART0);       // Enable the UART clock 
	__asm__("nop");                       // delay before access UART config registers 
	uart_disable(UART0);                  // Disable the UART while setting
	uart_clock_from_piosc(UART0);         // UART clock source as precision internal oscillator 
	uart_set_baudrate(UART0, 115200);     // Set communication parameters 
	uart_set_databits(UART0, 8);
	uart_set_parity(UART0, UART_PARITY_NONE);
	uart_set_stopbits(UART0, 1);
	uart_enable(UART0);                  
}
