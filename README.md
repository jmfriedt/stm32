Assumes libopencm3 is installed in $HOME/sat/arm-none-eabi (copy libraries in lib and header files in include)

For STM32F1-VL-Discovery board, 
```shell
ln -s Makefile.stm32f1
make
```

For STM32F4 based boards,
```shell
ln -s Makefile.stm32f4
make
```
