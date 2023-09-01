#include <vector>
#include <string>

#define INT_BITS 16

typedef struct OpCode {    
    unsigned short is:8;
    unsigned short p1:8;
    unsigned short p2:8;
    unsigned short p3:8;
   } OpCode;

typedef struct Peripherals {
    unsigned short intprint;
    unsigned short chrprint;
    unsigned short terminal;
    unsigned short keyboard;
} Peripherals;

typedef struct StatReg {//  --- Single 16 Bit Reg. (like others)---
    unsigned short nz:1;    // Accumilator != 0 flag
    unsigned short az:1;    // Accumilator == 0 flag
    unsigned short ac:1;    // Accumilator Carry flag
    unsigned short ms:1;    // Memory Swap flag
    unsigned short ao:4;    // Arithmatic Operation
    unsigned short pe:8;    // Peripheral Select
   } StatReg;

typedef struct StateH32 {
    unsigned short  a,b;        // Arithmatic Pair
    unsigned short  c,d,e,f;    // General Purpose registers
    struct StatReg  sr;         // Stat Register
    unsigned short  pc;         // Program Counter
    unsigned short  ao;         // Arithmatic Output
    unsigned short  io;         // IO Line
    struct OpCode  *rom;
    unsigned short *ram;     

   } StateH32;

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    std::ostream& operator<<(std::ostream& os, Code code) {
        return os << "\033[" << static_cast<int>(code) << "m";
    }
}

const char opSwap[16] = {'%','/','*','-','+','#','#','#','}','{','>','<','!','^','|','&'};

const char convert[128] = {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
                    'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z', '0', '[', ']', ',', '.', '-', '=', '`','\\',
                    '/','\'', ';', '\xDB', '\xDF', '\xFE', '\xDC', ' ', '\xAE', '\xAF', ' ', ' ', '\xC4', '\xC1', '\xC3',
                    ' ','\t', ' ','\n',
                    '\xFF', '!', '@', '#', '$', '%', '^', '&', '*', '(', 'A', 'B', 'C', 'D', 'E',
                    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                    'U', 'V', 'W', 'X', 'Y', 'Z', ')', '{', '}', '<', '>', '_', '+', '~','\xB3',
                    '?', '"', ':', ' ', ' ', ' ', ' ', ' ','\xD9','\xC0','\xDA','\xBF','\xC5','\xC2','\xB4',
                    ' ','\t', ' ','\n'};
