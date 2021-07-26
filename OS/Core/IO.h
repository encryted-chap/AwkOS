#pragma once
#include "Types.h"
inline void memcpy(unsigned char* from, unsigned char* to, char length) {
    asm volatile ("movb %0, %%ecx" : : "a"(length));
    asm volatile ("movsd %0, %%esi" : : "a"(&from));
    asm volatile ("movsd %0, %%edi" : : "a"(&to));
    asm volatile ("rep movsb");
}
inline void memcpy_w(unsigned char* from, unsigned char* to, char length) {
    asm volatile ("movb %0, %%ecx" : : "a"(length));
    asm volatile ("movsd %0, %%esi" : : "a"(&from));
    asm volatile ("movsd %0, %%edi" : : "a"(&to));
    asm volatile ("rep movsd");
}
inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
inline void outw(uint16_t port, uint16_t val) {
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}
inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile ( "inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
void SetRange(uint16_t* PortAddresses, uint8_t value) {
    for(int i = 0; PortAddresses[i] != (uint16_t)(char)'\0'; i++)
        outb(PortAddresses[i], value);
}