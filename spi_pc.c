#include <stdio.h>

void spi_clock_setup(void)
{
 printf("spi_clock_setup stub\n");
}

void spi_setup(void) {
 printf("spi_setup stub\n");
}

void spi_cs_low(void) {printf("CS# lo\n");}

void spi_cs_hi(void)  {printf("CS# hi\n");}

int spi_txrx(char c)
{ printf("SPI: sending %x",c);
  return(0xff);
}
