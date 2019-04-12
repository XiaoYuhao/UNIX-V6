#
# Makefile for Unix V6++ Login
#

#命令定义
CC = gcc
LD = ld

#参数定义
CFLAGS = -W -O0 -g -nostdlib -nostdinc -nostartfiles -fno-builtin -fno-exceptions

#目录定义
TARGET = .\OBJS
V6++LIB = "..\lib\Lib_V6++.a"
INCLUDE = .
LIB_INCLUDE = ..\lib\include

MAKEIMAGEPATH = ..\..\tools\MakeImage\bin\Debug\programs

.PHONY : all

LOGIN_OBJS =$(TARGET)\main.o
			
all	:	$(LOGIN_OBJS)
	$(CC) $(CFLAGS) $(LOGIN_OBJS) $(V6++LIB) -e _main1 -o $(TARGET)\Login.exe
	copy $(TARGET)\Login.exe $(MAKEIMAGEPATH)\Login.exe
	copy $(TARGET)\Login.exe $(MAKEIMAGEPATH)\Login2.exe
	
$(TARGET)\main.o :	main.c
	$(CC) $(CFLAGS) -I"$(INCLUDE)" -I"$(LIB_INCLUDE)" -c $< -o $@

clean:
	del $(TARGET)\*.o
	del $(TARGET)\*.exe
	