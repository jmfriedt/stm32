PROJ_NAME =test
CC=arm-none-eabi-gcc
SRCS=uart.o main_uart.o 


DRAPEAU =-Wall
DRAPEAU +=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4 
DRAPEAU +=--static -nostartfiles -L/home/diallo -Tstm32f4-discovery.ld
DRAPEAU +=-lopencm3_stm32f4 -I$(HOME)/sat/arm-none-eabi/include
LDFLAGS = -L$(HOME)/sat/arm-none-eabi/lib

all:$(PROJ_NAME).bin

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	arm-none-eabi-objcopy -Obinary $(PROJ_NAME).elf $(PROJ_NAME).bin

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(DRAPEAU) -o $(PROJ_NAME).elf $(SRCS) $(LDFLAGS) -lopencm3_stm32f4

uart.o: uart.c
	$(CC) $(DRAPEAU) -c uart.c

main_uart.o: main_uart.c
	$(CC) $(DRAPEAU) -c main_uart.c


clean:
	rm *.o $(PROJ_NAME).elf $(PROJ_NAME).bin

flash: $(PROJ_NAME).bin
	st-flash write $(PROJ_NAME).bin 0x8000000
	#stm32flash.sh -w $(PROJ_NAME).bin /dev/ttyUSB0





