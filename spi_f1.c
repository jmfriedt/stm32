#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/spi.h>

void spi_clock_setup(void)
{
 rcc_periph_clock_enable(RCC_GPIOB); // SPI2 = PORTB ; GPIOB12 = manual CS#
 rcc_periph_clock_enable(RCC_AFIO);
 rcc_periph_clock_enable(RCC_SPI2);
}

void spi_setup(void) {
  /* Configure GPIOs: SS=PB12, SCK=PB13, MISO=PB14 and MOSI=PB15 */
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
            GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO13 | GPIO15 );
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
            GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
  gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
            GPIO14);

  /* Reset SPI, SPI_CR1 register cleared, SPI is disabled */
  rcc_periph_reset_pulse(RST_SPI1); // see https://github.com/libopencm3/libopencm3/pull/268

  /* Set up SPI in Master mode with:
   * Clock baud rate: 1/64 of peripheral clock frequency
   * Clock polarity: Idle High
   * Clock phase: Data valid on 1st clock pulse
   * Data frame format: 8-bit
   * Frame format: MSB First
   */
  spi_init_master(SPI2, SPI_CR1_BAUDRATE_FPCLK_DIV_128, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
                  SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);

  /*
   * Set NSS management to software.
   *
   * Note:
   * Setting nss high is very important, even if we are controlling the GPIO
   * ourselves this bit needs to be at least set to 1, otherwise the spi
   * peripheral will not send any data out.
   */
   //spi_enable_software_slave_management(SPI2);
   //spi_set_nss_high(SPI2);

  /* Enable SPI2 periph. */
  spi_enable(SPI2);
}

void spi_cs_low(void) {gpio_clear(GPIOB, GPIO12);}

void spi_cs_hi(void)  {gpio_set  (GPIOB, GPIO12);}

int spi_txrx(char c)
{ spi_send(SPI2,c); 
  return(spi_read(SPI2));   // always read after write to avoid averflow
}
