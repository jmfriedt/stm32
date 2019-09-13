#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/flash.h> // definitions du timer

#define netwk

// APB2 max=84 MHz but when the APB prescaler is NOT 1, the interface clock is fed
// twice the frequency => Sysclk = 140 MHz, APB2=2 but Timers are driven at twice that is 140.
const struct rcc_clock_scale rcc_hse_20mhz_3v3 = {
                .pllm = 20,                           // 20/20=1 MHz
                .plln = 280,                          // 1*280/2=140 MHz
                .pllp = 2,                            //       ^
                .pllq = 6,
		.pllr=0,
		.pll_source = RCC_CFGR_PLLSRC_HSE_CLK, // 190913 mandatory to use external clock (!=HSI)
                .hpre = RCC_CFGR_HPRE_DIV_NONE,
                .ppre1 = RCC_CFGR_PPRE_DIV_4,
                .ppre2 = RCC_CFGR_PPRE_DIV_2,
		.voltage_scale = PWR_SCALE1,
                .flash_config = FLASH_ACR_ICEN | FLASH_ACR_DCEN |
                                FLASH_ACR_LATENCY_4WS, // 4 WS d'apres configuration par ST
                .ahb_frequency  = 140000000,  
                .apb1_frequency = 35000000,    
                .apb2_frequency = 70000000,
        };

/**
  * @file    system_stm32f4xx.c
  * @author  MCD Application Team
  *=============================================================================
  *        Supported STM32F40xx/41xx/427x/437x devices
  *        System Clock source                    | PLL (HSE)
  *        SYSCLK(Hz)                             | 140000000
  *        HCLK(Hz)                               | 140000000
  *        AHB Prescaler                          | 1
  *        APB1 Prescaler                         | 4
  *        APB2 Prescaler                         | 2
  *        HSE Frequency(Hz)                      | 20000000
  *        PLL_M                                  | 20
  *        PLL_N                                  | 280
  *        PLL_P                                  | 2
  *        PLL_Q                                  | 6
  *        Flash Latency(WS)                      | 4
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
*/

void core_clock_setup(void)
{
 	// rcc_clock_setup_hse_3v3(&rcc_hse_20mhz_3v3); // custom version
	rcc_clock_setup_pll(&rcc_hse_20mhz_3v3);
}

void mon_putchar(unsigned char ch)
{
	usart_send_blocking(USART1, ch);
	usart_send_blocking(USART2, ch);
}

void mon_puts(char *buf)
{
	int i=0; // nbre de caractère initialisé à 0
	char tmp=0; // caractere actuels
	do
	{
		tmp=buf[i];
		i++;
		mon_putchar(tmp);
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
	/* Setup GPIO for LED. */
#ifdef netwk
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO11|GPIO12|GPIO13);
#else
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12|GPIO15);
#endif

	/* Setup GPIO pins for USART2 transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9); //TX
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10); //RX

	/* Setup USART1 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF7, GPIO9);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO10);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2); //TX
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3); //RX

	/* Setup USART1 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO3);
}

void clock_setup(void)
{
// for STM32F4-Disco
// 	rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

// for DDS-based project
	core_clock_setup();
	/* Enable GPIOD clock for LED & USARTs. */
#ifdef netwk
	rcc_periph_clock_enable(RCC_GPIOA);
#else
	rcc_periph_clock_enable(RCC_GPIOD);
#endif

	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_USART2);
}


void led_set(int msk)
{
#ifdef netwk
	gpio_set(GPIOA, msk);
#else
	gpio_set(GPIOD, GPIO15|GPIO12);
#endif
}

void led_clr(int msk)
{
#ifdef netwk
	gpio_clear(GPIOA, msk);
#else
	gpio_clear(GPIOD, GPIO15|GPIO12);
#endif
}

void usart_setup(void)
{
	/* Setup USART1 parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
	
        /* Setup USART2 parameters. */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART2);
}
