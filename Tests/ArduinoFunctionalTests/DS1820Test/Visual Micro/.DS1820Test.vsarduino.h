#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Duemilanove w/ ATmega328
#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

void WriteUpdate(uint8_t* buffer, size_t numberOfBytes);
//
//

#include "D:\Installs\Engineering Tools\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "D:\Installs\Engineering Tools\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "D:\Code\HAS\Arduino\Tests\ArduinoFunctionalTests\DS1820Test\DS1820Test.ino"
#endif
