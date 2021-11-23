#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/spi.h>

void spi_clock_setup(void);
void spi_setup(void);
int spi_txrx(char);
void spi_cs_low(void);
void spi_cs_hi(void);
