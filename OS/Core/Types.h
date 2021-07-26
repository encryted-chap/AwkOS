#pragma once
#include "Bitwise.h"

typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef long int_least32_t;
typedef long long int_least64_t;

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned long uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef long int_fast32_t;
typedef long long int_fast64_t;

typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned long uint_fast32_t;
typedef unsigned long long uint_fast64_t;

typedef long intptr_t;
typedef unsigned long uintptr_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;

// a byte which allows you to alter its bits
class bt_byte {
public:
    bt_byte(unsigned char byte) {
        BYTE = byte;
        for(int i = 0; i < 8; i++) {
            bitarray[i] = GetBit(BYTE, i+1);
        }
    }
    bool operator[](int index) {
        if(index > 7) return false;
        else return *(bitarray+index);
    }
    void Set(int index) {
        bitarray[index] = true;
        Update();
    }
    void Clear(int index) {
        bitarray[index] = false;
        Update();
    }
    unsigned char operator=(unsigned char other) {
        return BYTE;
    }
    unsigned char operator<<(unsigned char other) {
        return BYTE << other;
    }
    unsigned char operator>>(unsigned char other) {
        return BYTE >> other;
    }
    unsigned char operator^(unsigned char other) {
        return BYTE ^ other;
    }
    unsigned char operator&(unsigned char other) {
        return BYTE&other;
    }
    operator char() const {
        return BYTE;
    }
private:
    void Update() {
        for(int i = 0; i < 8; i++) {
            if(bitarray[i]) 
                BYTE = SetBit(BYTE, i+1);
            else {
                if(GetBit(BYTE, i+1)) {
                    ToggleBit(&BYTE, i+1);
                }
            }
        }
    }
    bool* bitarray;
    unsigned char BYTE;
};
template<class TKey, class TValue> class Dictionary {
public:
    int length = 0;
    Dictionary() {}
    void Add(TKey key, TValue value) {
        keys[length] = key;
        values[length++] = value;
    }
    TValue operator[](TKey key) {
        for(int i = 0; i < length; i++) {
            if(keys[i] == key)
                return values[i];
        }
    }
private:
    TKey* keys;
    TValue* values;
};
class string {
public:
    int Length = 0;
    string(char* str) {
        BUFF = "";
        for(int i = 0; str[i] != '\0'; i++, Length++)
            BUFF[i] = str[i];
    }
    // returns true if this string is requesting another
    // strings buffer. Used to make sure no pesky
    // devs try to hijack a string's buffer
    bool IsRequesting() {
        return requesting;
    }
    // requests a buffer from this string, must be called
    // with a string that is requesting already
    char* GetRequest(string whois) {
        if(whois.IsRequesting())
            return BUFF;
        else return "";
    }
    // requests from another string, returns whether the request returned a non-empty string
    bool RequestFrom(string whois) {
        requesting = true;
        Requested = whois.GetRequest(*this);
        requesting = false;
        return (Requested != "");
    }
    string* operator=(string other) {
        if(RequestFrom(other)) {
            BUFF = Requested;
        } else {
            BUFF = "";
        }
        return this;
    }
    char operator[](int index) {
        return BUFF[index];
    }
    string Clone(string toClone) {
        RequestFrom(toClone);
        return string(Requested);
    }
    string Remove(int index) {
        string ret = Clone(*this);
        
    }
private:
    bool requesting = false;
    char* Requested;
    char* BUFF;
};