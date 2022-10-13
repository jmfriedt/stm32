#include <stdio.h>

void core_clock_setup(void)
{
}

void my_putchar(unsigned char ch)
{
	printf("%c", ch);
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
}

void clock_setup(void)
{
}


void led_set(int msk)
{
	printf("\nallume LED\n");
}

void led_clr(int msk)
{
	printf("\neteint LED\n");
}

void usart_setup(void)
{
}
