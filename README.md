Assumes libopencm3 (https://github.com/libopencm3/libopencm3) is installed (``git clone https://github.com/libopencm3/libopencm3 && cd libopencm3 && make``): make sure to adapt
-L and -I options to your directory structure so that libraries and header files are found at compile time.

For STM32F1(00)-VL-Discovery board, 
```shell
ln -s Makefile.stm32f100 Makefile
make
```

For STM32F4 based boards,
```shell
ln -s Makefile.stm32f4 Makefile
make
```

For STM32F1(03) based boards,
```shell
ln -s Makefile.stm32f1 Makefile
make
```

For running on qemu, install Andre Beckus version of qemu for STM32 as found at
https://github.com/beckus/qemu_stm32 and
```shell
make -f Makefile.stm32f1 qemu
```

The software architecture is organized to provide functions with the same prototype (input
and output arguments) for various microcontroller architectures and select upon linking
which version is used with portable, common main functions. Start with ``main_uart.c`` as
a basic example, and link the appropriate ``Makefile.*`` to ``Makefile`` (ln -s) to compile
for the given target using ``make``.

## Issue

In case the STM32VL-Discovery board returns
```
2025-01-28T20:14:56 INFO flashloader.c: Starting Flash write for VL/F0/F3/F1_XL
2025-01-28T20:14:56 INFO flash_loader.c: Successfully loaded flash loader in sram
2025-01-28T20:14:56 INFO common.c: Go to Thumb mode
2025-01-28T20:14:56 ERROR flash_loader.c: Flash loader run error
...
```
then <a href="https://community.st.com/t5/stm32-mcus-products/how-to-unbrick/td-p/552609">connect
pin BOOT to 3.3V</a> and reset before launching ``st-flash``.
