#pragma once

// sets a single bit in a number
unsigned char SetBit(unsigned char byte_to_set, int bit_to_set) {
    byte_to_set |= 1UL << (bit_to_set - 1);
}
// gets a bit in a byte
bool GetBit(unsigned char byte_to_read, int bit_to_read) {
    byte_to_read &= ~(1UL << bit_to_read-1);
    return (bool)(byte_to_read);
}

// toggles a single bit in a byte
void ToggleBit(unsigned char* byte_to_toggle, int bit_to_toggle) {
    byte_to_toggle[0] ^= 1UL << bit_to_toggle;
}

// creates a bitmask which can be ANDed with a number to extract bits a-b
unsigned int CreateMask(unsigned a, unsigned b)
{
   unsigned int r = 0;
   for (unsigned int  i=a; i<=b; i++)
       r |= 1 << i;
   return r;
}