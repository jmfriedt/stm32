Assumes libopencm3 (https://github.com/libopencm3/libopencm3) is installed (``git clone https://github.com/libopencm3/libopencm3 && cd libopencm3 && make``): make sure to adapt
-L and -I options to your directory structure so that libraries and header files are found at compile time.

For STM32F1(00)-VL-Discovery board, 
```shell
ln -s Makefile.stm32f1
make
```

For STM32F4 based boards,
```shell
ln -s Makefile.stm32f4
make
```

For STM32F1(03) based boards,
```shell
ln -s Makefile.stm32f1  
make
```
