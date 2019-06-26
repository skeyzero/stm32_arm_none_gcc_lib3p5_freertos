# stm32 工程  包含 Lib3.5官方库 FreeRTOS Ver10.2.1

## 环境参数
* archlinux--linux-kernel-4.19.28s
* arm-none-eabi-gcc
* stm32 Lib3.5
* FreeRTOS10.2.1
## Archlinux Software-Needed
* arm-none-eabi-binutils
* arm-none-eabi-gcc
* arm-none-eabi-gdb
* arm-none-eabi-newlib
* stlink

## Directory structure
> makefile    
>> usr ---- user's source files place here    
>> output ---- compiler output    
>> lib ---contains startup files and libs...   
>> src ---底层一些库，非完整版
>> FreeRTOS --- FreeRTOS内核相关
## Usage    
* Copy to your project directory     

## makefile 
see more in makefile

## Updates：   
>2018.12.21      
* optimize makefile   
>2019.02.11   
*修改makefile,将输出文件整理到output文件夹内    
>2019.06.26
* 移植FreeRTOS系统

## 例程说明   
使用STM32F103VET6---512kFlash---64kRAM    
例程每500ms打印一次 "Welcome to Freertos".串口5配置：115200,8,N，1
## 编译：
	make
## stlink下载：
	make load
## 清除编译选项
	make clean
	
## 相关咨询，可加群一起学习讨论
QQ:81154350       备注:开源电子电路开发
